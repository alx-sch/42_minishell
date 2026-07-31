# minishell

<p align="center">
    <img src="https://raw.githubusercontent.com/alx-sch/minishell/refs/heads/main/.assets/minishell-badge.png" alt="minishell badge" width="150" />
</p>

A simplified bash-like shell written in C, built from scratch as part of the 42 Berlin curriculum. Minishell implements the core mechanics of a Unix shell — lexical analysis, parsing, variable expansion, process management, piping, and I/O redirection — providing a hands-on exploration of how shells actually work under the hood.

**Collaborator:** [Natalie Holbrook](https://github.com/busedame)

**Supports:**
- Interactive command-line with readline (history, line editing)
- Pipes (`|`) chaining multiple commands
- Redirections: input (`<`), output (`>`), append (`>>`), heredoc (`<<`)
- Environment variable expansion (`$VAR`, `$?`)
- Quoting: single quotes (literal), double quotes (with expansion)
- Signal handling: `CTRL+C`, `CTRL+D`, `CTRL+\`
- Persistent command history across sessions
- 7 builtin commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`

---

<div id="top"></div>

## Overview

- [How to Use](#-how-to-use)
- [Architecture](#architecture)
  - [The Main Loop](#the-main-loop)
  - [Data Structures](#data-structures)
- [Stage 1: Input Validation](#stage-1-input-validation)
- [Stage 2: Tokenization (Lexical Analysis)](#stage-2-tokenization-lexical-analysis)
  - [What Is a Token?](#what-is-a-token)
  - [The Tokenizer Algorithm](#the-tokenizer-algorithm)
- [Stage 3: Parsing](#stage-3-parsing)
  - [Heredoc Processing](#heredoc-processing)
  - [Variable Expansion](#variable-expansion)
  - [Quote Removal](#quote-removal)
- [Stage 4: Execution](#stage-4-execution)
  - [Parent vs. Child Builtins](#parent-vs-child-builtins)
  - [Pipes and Process Creation](#pipes-and-process-creation)
  - [Redirections](#redirections)
  - [PATH Resolution](#path-resolution)
- [Signal Handling](#signal-handling)
- [Builtins](#builtins)
- [Acknowledgements](#acknowledgements)
- [References](#references)

---

## 🚀 How to Use

1. **Clone the repository:**
   ```bash
   git clone https://github.com/alx-sch/minishell.git
   cd minishell
   ```

2. **Build:**
   ```bash
   make
   ```
   This compiles the custom `libft` library and the minishell binary. Requires `readline` and `history` libraries installed on your system.

3. **Run:**
   ```bash
   ./minishell
   ```

4. **Example session:**
   ```
   minishell$ echo "Hello, World!"
   Hello, World!
   minishell$ ls -la | grep ".c" | wc -l
   56
   minishell$ export MY_VAR="42 Berlin"
   minishell$ echo $MY_VAR
   42 Berlin
   minishell$ cat << EOF
   > line one
   > line two
   > EOF
   line one
   line two
   minishell$ exit
   ```

<div align="right"><b><a href="#top">back to top</a></b></div>

---

## Architecture

### The Main Loop

At its core, a shell is a REPL — Read, Evaluate, Print, Loop. Minishell's main loop orchestrates a linear pipeline of stages, each transforming the user's raw input one step closer to execution:

```
┌─────────────────────────────────────────────────────────────┐
│                        MAIN LOOP                            │
│                                                             │
│   ┌───────────┐    ┌───────────┐    ┌─────────┐            │
│   │  Prompt   │───>│  Validate │───>│Tokenize │            │
│   │ (readline)│    │  (quotes) │    │ (lexer) │            │
│   └───────────┘    └───────────┘    └────┬────┘            │
│                                          │                  │
│   ┌───────────┐    ┌───────────┐    ┌────▼────┐            │
│   │  Cleanup  │<───│  Execute  │<───│  Parse  │            │
│   │  (free)   │    │(fork/exec)│    │(expand) │            │
│   └───────────┘    └───────────┘    └─────────┘            │
│         │                                                   │
│         └──────────────── loop ─────────────────────────────│
└─────────────────────────────────────────────────────────────┘
```

Each iteration:
1. **Signal setup** — registers handlers for the current context (prompt mode)
2. **Prompt** — reads user input via `readline()`
3. **Validate** — rejects empty input and unclosed quotes
4. **Tokenize** — splits input into a linked list of typed tokens
5. **Parse** — processes heredocs, expands variables, removes quotes
6. **Execute** — forks child processes, sets up pipes/redirections, runs commands
7. **Cleanup** — frees all allocated memory for the current iteration

This design mirrors the front-end of a compiler<sup><a href="#footnote1">[1]</a></sup>: lexical analysis (tokenization) produces tokens, and parsing transforms them into a structure suitable for interpretation (execution).

<div align="right"><b><a href="#top">back to top</a></b></div>

---

### Data Structures

The central `t_data` structure holds the entire shell state. Rather than passing dozens of parameters between functions, everything lives in one place:

```c
typedef struct s_data
{
    int             argc;
    char            **argv;
    char            **envp;             // original envp from main()
    char            *input;             // current user input line
    int             pipe_nr;            // number of pipes in current command
    unsigned int    exit_status;        // last command's exit code ($?)
    char            *working_dir;       // current working directory
    char            *path_to_hist_file; // persistent history file path
    t_tok           tok;                // tokenizer state + token linked list
    t_env           *envp_temp;         // environment as a doubly-linked list
    t_env           *export_list;       // sorted export list (for `export`)
    t_cd            cd;                 // cd builtin state
    t_quote         quote;             // quote-tracking during parsing
} t_data;
```

**Why a linked list for tokens?** A shell command can have an arbitrary number of tokens. Linked lists allow dynamic growth without pre-allocating a fixed-size array, and make insertion/deletion trivial during the parsing stage when heredoc tokens get rewritten.

**Why two environment lists?** Bash maintains separate state for `env` (only variables with values) and `export` (includes declared-but-unset variables, displayed alphabetically). Two lists mirror this behavior cleanly.

<div align="right"><b><a href="#top">back to top</a></b></div>

---

## Stage 1: Input Validation

Before any processing begins, the shell performs quick sanity checks:

| Check | What it catches | Example |
|:------|:----------------|:--------|
| Empty input | User pressed Enter with no text | ` ` |
| Whitespace-only | Spaces/tabs but no command | `   \t  ` |
| Unclosed quotes | Missing closing `'` or `"` | `echo "hello` |

The quote validator tracks position so it can report *where* the unclosed quote starts — a usability detail that helps the user locate their mistake.

If validation fails, the shell skips directly to cleanup and re-prompts without wasting time on tokenization.

<div align="right"><b><a href="#top">back to top</a></b></div>

---

## Stage 2: Tokenization (Lexical Analysis)

### What Is a Token?

Tokenization (or lexical analysis) is the process of breaking a raw string into meaningful units called *tokens*<sup><a href="#footnote1">[1]</a></sup>. Each token has a **type** and a **lexeme** (its string value):

```c
typedef enum e_token_type
{
    PIPE,       // |
    REDIR_IN,   // <
    REDIR_OUT,  // >
    APPEND_OUT, // >>
    HEREDOC,    // <<
    OTHER,      // commands, arguments, filenames
} t_token_type;

typedef struct s_token
{
    t_token_type    type;
    char            *lexeme;
    int             position;
} t_token;
```

For example, the input `cat -n file.txt | grep "hello" > out.txt` produces:

| Position | Type | Lexeme |
|:--------:|:-----|:-------|
| 0 | OTHER | `cat` |
| 1 | OTHER | `-n` |
| 2 | OTHER | `file.txt` |
| 3 | PIPE | `\|` |
| 4 | OTHER | `grep` |
| 5 | OTHER | `"hello"` |
| 6 | REDIR_OUT | `>` |
| 7 | OTHER | `out.txt` |

### The Tokenizer Algorithm

The tokenizer uses a **quote-aware delimiter scan** — it iterates character by character, but characters inside quotes are never treated as delimiters:

```
for each character in input:
    skip whitespace
    if character is '<' or '>'  → create REDIR token (check for << / >>)
    if character is '|'         → create PIPE token
    otherwise                   → scan until next delimiter, create OTHER token
```

**Quote awareness** is critical. In `echo "hello | world"`, the `|` is inside double quotes, so the tokenizer must *not* split on it. The `is_delimiter()` function tracks whether it is inside a quoted region and only recognizes delimiters when outside quotes.

**Syntax validation** happens during tokenization:
- A pipe cannot appear at the start or end of input (`| ls` or `ls |`)
- Two pipes cannot be adjacent (`ls || grep`)
- A redirection must be followed by a filename (`> ` with nothing after)

<div align="right"><b><a href="#top">back to top</a></b></div>

---

## Stage 3: Parsing

After tokenization, the parser transforms the token list into its final form ready for execution. This happens in three sub-stages:

### Heredoc Processing

A heredoc (`<<`) lets the user provide multi-line input inline. The challenge: by the time execution happens, the shell needs a *file descriptor* to read from — not an interactive prompt. Minishell solves this elegantly by **converting heredocs into regular input redirections at parse time**:

```
Before parsing:   << EOF
                  (token: HEREDOC)  (token: "EOF")

User types:       hello
                  world
                  EOF

After parsing:    < .heredoc_0
                  (token: REDIR_IN)  (token: ".heredoc_0")
```

The parser:
1. Detects `HEREDOC` tokens
2. Prompts the user line-by-line (using `readline("> ")`) until the delimiter appears
3. Writes all collected lines to a temporary file (`.heredoc_0`, `.heredoc_1`, etc.)
4. Replaces the `HEREDOC` + delimiter tokens with `REDIR_IN` + filename tokens

This transformation means the execution stage doesn't need to know heredocs exist — it just sees regular input redirections.

### Variable Expansion

Variable expansion replaces `$VAR` references with their values from the environment. The algorithm walks through each token's lexeme character by character:

```
for each character:
    if inside single quotes → skip (no expansion)
    if '$' followed by alphanumeric → extract var name, look up value, splice in
    if '$?' → replace with last exit status
```

**Splicing** is the key operation: the string is split into three parts (left of `$`, the value, right of the var name), then concatenated. This handles variables of any length replacing references of any length.

**Single quotes suppress expansion** — this is a fundamental shell rule. `'$HOME'` outputs the literal string `$HOME`, while `"$HOME"` expands to `/Users/username`.

### Quote Removal

After expansion, paired quotes are stripped from token lexemes. The quotes served their purpose (controlling delimiter recognition and expansion behavior) and are no longer needed.

`"hello"` becomes `hello`. `'$HOME'` becomes `$HOME`.

<div align="right"><b><a href="#top">back to top</a></b></div>

---

## Stage 4: Execution

### Parent vs. Child Builtins

Not all commands can run in a child process. Some builtins *must* execute in the parent because they modify shell state:

| Parent builtins | Why |
|:----------------|:----|
| `cd` | Changes the parent's working directory |
| `export` (with args) | Modifies the parent's environment lists |
| `unset` | Removes variables from the parent's environment |
| `exit` | Terminates the parent process |

If minishell forks a child and runs `cd` there, the child's working directory changes — then the child exits, and the parent is still in the old directory. This is why real shells execute these builtins in the parent process<sup><a href="#footnote2">[2]</a></sup>.

**When there are no pipes**, minishell checks if the command is a parent builtin and runs it directly. When pipes are involved, even parent builtins run in children (since they form part of a pipeline and their output needs to be piped).

### Pipes and Process Creation

A pipe (`|`) connects the stdout of one command to the stdin of the next. For $n$ pipes, the shell creates $n + 1$ child processes:

```
ls -la | grep ".c" | wc -l

        pipe[0]         pipe[1]
    ┌──────────────┐ ┌──────────────┐
    │  fd[0] fd[1] │ │  fd[0] fd[1] │
    └──────────────┘ └──────────────┘
         ▲    │           ▲    │
         │    ▼           │    ▼
   ┌─────┴──┐  ┌────────┴─┐  ┌───────┐
   │  ls -la │  │ grep ".c" │  │ wc -l │
   │ (child0)│  │  (child1) │  │(child2)│
   └─────────┘  └──────────┘  └───────┘
   stdout→fd[1]  stdin←fd[0]   stdin←fd[0]
                 stdout→fd[1]
```

The implementation iterates through the token list, forking one child per pipe-separated segment. Each child:
1. Closes unused pipe ends
2. Redirects stdin/stdout via `dup2()` to the appropriate pipe file descriptors
3. Calls `execve()` (or runs the builtin)

The parent tracks previous pipe file descriptors so it can close them after the next fork — preventing file descriptor leaks that would cause children to hang waiting for EOF on a pipe that's still open.

### Redirections

Redirections reroute a command's stdin or stdout to/from files. The shell scans the token list for redirection operators and records the last one of each type (matching bash behavior — `> a > b > c` only writes to `c`):

```c
// Pseudocode for redirection setup
if (redir_in)   → open(infile, O_RDONLY)           → dup2(fd, STDIN)
if (redir_out)  → open(outfile, O_WRONLY|O_TRUNC)  → dup2(fd, STDOUT)
if (append_out) → open(outfile, O_WRONLY|O_APPEND) → dup2(fd, STDOUT)
```

**Redirection and pipe interaction:** If a command has both a pipe and a redirection, the redirection takes precedence. In `ls | cat > file`, cat's stdout goes to `file`, not the next pipe.

### PATH Resolution

When a command doesn't contain a `/` character, the shell searches for it in the directories listed in `$PATH`:

1. Split `$PATH` by `:` into an array of directories
2. For each directory, concatenate `directory/command`
3. Check if the resulting path is executable (`access()` with `X_OK`)
4. Use the first match

If the command contains `/`, it's treated as a direct path (absolute or relative) — no PATH search is performed.

<div align="right"><b><a href="#top">back to top</a></b></div>

---

## Signal Handling

Unix signals are asynchronous notifications sent to a process. Minishell handles them differently depending on context — because what the user expects from `CTRL+C` changes based on what's happening:

| Signal | Prompt | Heredoc | Execution |
|:-------|:-------|:--------|:----------|
| `SIGINT` (CTRL+C) | Clear line, new prompt | Cancel heredoc input | Terminate child, print newline |
| `SIGQUIT` (CTRL+\\) | Ignored | Ignored | Print "Quit (core dumped)" |
| EOF (CTRL+D) | Print "exit", terminate shell | Cancel heredoc | — |

The global variable `volatile __sig_atomic_t g_signal` communicates between the signal handler (which runs asynchronously) and the main loop. The `volatile` and `__sig_atomic_t` qualifiers ensure the compiler doesn't optimize away reads of this variable, and that reads/writes are atomic<sup><a href="#footnote3">[3]</a></sup>.

**Why three different signal modes?** Consider `CTRL+C`:
- At the prompt, the user wants to cancel what they're typing and get a fresh prompt
- During heredoc input, they want to abort the heredoc and return to the prompt
- During command execution, they want to kill the running command

Each context installs different signal handlers via `signal()`, switching between them as the shell transitions through its stages.

<div align="right"><b><a href="#top">back to top</a></b></div>

---

## Builtins

Builtins are commands implemented directly in the shell rather than as external programs. They're necessary either because they modify shell state (impossible from a child process) or because launching a separate process would be needlessly expensive:

| Builtin | Usage | Description |
|:--------|:------|:------------|
| `echo` | `echo [-n] [text...]` | Print arguments to stdout; `-n` suppresses trailing newline |
| `cd` | `cd [path]` | Change working directory; supports `~`, `..`, absolute, relative |
| `pwd` | `pwd` | Print current working directory |
| `export` | `export [NAME[=value]...]` | Without args: print sorted export list; with args: set variables |
| `unset` | `unset [NAME...]` | Remove variables from the environment |
| `env` | `env` | Print all environment variables with values |
| `exit` | `exit [n]` | Exit the shell with status `n` (default 0); validates numeric arg |

<div align="right"><b><a href="#top">back to top</a></b></div>

---

## Acknowledgements

- Built by [Alexander Schenk](https://github.com/alx-sch) and [Natalie Holbrook](https://github.com/busedame) at 42 Berlin, August 2024.
- The project badge is from [this repository](https://github.com/ayogun/42-project-badges) by Ali Ogun.
- The wonderful *Crafting Interpreters*<sup><a href="#footnote1">[1]</a></sup> by Robert Nystrom provided conceptual grounding on tokenization and parsing.

---

## References

<a name="footnote1">[1]</a> Nystrom, R. (2021). *Crafting Interpreters*. Genever Benning. Available at: <a href="https://craftinginterpreters.com" target="_blank">https://craftinginterpreters.com</a> <br>
<a name="footnote2">[2]</a> Rodriguez-Rivera, G. & Ennen, J. (2014). *Introduction to Systems Programming: a Hands-on Approach*, Chapter 5: Writing Your Own Shell. Purdue University. Available at: <a href="https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf" target="_blank">https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf</a> <br>
<a name="footnote3">[3]</a> Free Software Foundation. (2023). *The GNU Bash Reference Manual*. Available at: <a href="https://www.gnu.org/software/bash/manual/bash.html" target="_blank">https://www.gnu.org/software/bash/manual/bash.html</a> <br>
<a name="footnote4">[4]</a> Brennan, S. (2015). *Tutorial — Write a Shell in C*. Available at: <a href="https://brennan.io/2015/01/16/write-a-shell-in-c/" target="_blank">https://brennan.io/2015/01/16/write-a-shell-in-c/</a> <br>
<a name="footnote5">[5]</a> Backus-Naur Form. *Wikipedia*. Available at: <a href="https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form" target="_blank">https://en.wikipedia.org/wiki/Backus–Naur_form</a>
