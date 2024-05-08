# 42_minishell

This project is about creating a simple shell. 

We will be inspired by Bash. Bash is an acronym for ‘Bourne-Again SHell’.  Below are some exerpts from the bash manual.

### allowed functions

readline, rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,
printf, malloc, free, write, access, open, read,
close, fork, wait, waitpid, wait3, wait4, signal,
sigaction, sigemptyset, sigaddset, kill, exit,
getcwd, chdir, stat, lstat, fstat, unlink, execve,
dup, dup2, pipe, opendir, readdir, closedir,
strerror, perror, isatty, ttyname, ttyslot, ioctl,
getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
tgetnum, tgetstr, tgoto, tputs


## what is a shell
Shells may be used interactively or non-interactively. In interactive mode, they accept input typed from the keyboard. When executing non-interactively, shells execute commands read from a file.

A shell allows execution of GNU commands, both synchronously and asynchronously. The shell waits for synchronous commands to complete before accepting more input; asynchronous commands continue to execute in parallel with the shell while it reads and executes additional commands. The redirection constructs permit fine-grained control of the input and output of those commands. Moreover, the shell allows control over the contents of commands’ environments.

Shells also provide a small set of built-in commands (builtins) implementing functionality impossible or inconvenient to obtain via separate utilities. For example, cd, break, continue, and exec cannot be implemented outside of the shell because they directly manipulate the shell itself. The history, getopts, kill, or pwd builtins, among others, could be implemented in separate utilities, but they are more convenient to use as builtin commands. All of the shell builtins are described in subsequent sections.

## Shell Syntax (from the BASH manual)

When the shell reads input, it proceeds through a sequence of operations. If the input indicates the beginning of a comment, the shell ignores the comment symbol (‘#’), and the rest of that line.

Otherwise, roughly speaking, the shell reads its input and divides the input into words and operators, employing the quoting rules to select which meanings to assign various words and characters.

The shell then parses these tokens into commands and other constructs, removes the special meaning of certain words or characters, expands others, redirects input and output as needed, executes the specified command, waits for the command’s exit status, and makes that exit status available for further inspection or processing.

## The map
- we start by implementing a loop that reads the user input with the readline() function. The readline function is part of the part of the GNU Readline library and offers other functions like rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay,add_history that we are allowed to use in our project.
- The first step is scanning, also known as lexing, or (if you’re trying to impress someone) lexical analysis.
- A scanner (or lexer) takes in the linear stream of characters and chunks them together into a series of something more akin to “words”. In programming languages, each of these words is called a token. Some tokens are single characters, like ( and , . Others may be several characters long, like numbers ( 123 ), string literals ( "hi!" ), and identifiers ( min ).
- The next step is parsing. This is where our syntax gets a grammar—the ability to compose larger expressions and statements out of smaller parts. 
A parser takes the flat sequence of tokens and builds a tree structure that mirrors the nested nature of the grammar. These trees have a couple of different names—“parse tree” or “abstract syntax tree”In practice, language hackers usually call them “syntax trees”, “ASTs”, or often just “trees”.
- Everything up to this point is considered the front end of the implementation.
- Tree-walk interpreters 
 To run the program, the interpreter traverses the syntax tree one branch and leaf at a time, evaluating each node as it goes.
- we have a number of builtins we will implement. These are 
◦ echo with option -n
◦ cd with only a relative or absolute path 
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options

- Our shell should also have a working history.



## Context free grammar

I really liked the explanation of context-free grammar in the book Crafting Interpreters. Looking in chapter 4 of the book, it explains that the first step is scanning. 

> Scanning is a good starting point for us too because the code isn’t very hard—pretty much a switch statement with delusions of grandeur.

A scanner (or lexer) takes in the linear stream of characters and chunks them together into a series of something more akin to “words”. In programming languages, each of these words is called a token. Some tokens are single characters, like ( and , . Others may be several characters long, like numbers ( 123 ), string literals ( "hi!" ), and identifiers ( min ). The next step is parsing. This is where our syntax gets a grammar—the ability to compose larger expressions and statements out of smaller parts. A parser takes the flat sequence of tokens and builds a tree structure that mirrors the nested nature of the grammar. These trees have a couple of different names—“parse tree” or “abstract syntax tree”. In practice, language hackers usually call them “syntax trees”, “ASTs”, or often just “trees”. Everything up to this point is considered the front end of the implementation. The back end is where the interpreter actually runs the program. There are a few different ways to do this, but the most common is tree-walk interpreters. To run the program, the interpreter traverses the syntax tree one branch and leaf at a time, evaluating each node as it goes.

We need to create our grammar. to do so we head to our Bash manual!

Some of the definitions there are interesting to us:
- blank
	A space or tab character.
- word
	A sequence of characters considered as a single unit by the shell. Also known as a token.
- name
	A word consisting only of alphanumeric characters and underscores, and beginning with an alphabetic character or an underscore. Also referred to as an identifier.
- metacharacter
	A character that, when unquoted, separates words. A metacharacter is a space, tab, newline, or one of the following characters: ‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, or ‘>’.
- control operator
	A token that performs a control function. It is a newline or one of the following: ‘||’, ‘&&’, ‘&’, ‘;’, ‘;;’, ‘;&’, ‘;;&’, ‘|’, ‘|&’, ‘(’, or ‘)’.
- operator
	A sequence of characters considered a single unit by the shell. It is either a word or an operator.
- reserved word
	A word that has a special meaning to the shell. Most reserved words introduce shell flow control constructs, such as loops or conditionals. The reserved words recognized by the shell are: `! case do done elif else esac fi for if in then until while { } time [[ ]]`

I think this is a good starting point for our grammar. We can start by defining the tokens that we will use in our shell.

also there is the question of priority. I would call them commands and not expression like a compiler would.

&& and || have the same precedence and are left-associative. They allow you to execute a command based on the success (&&) or failure (||) of the previous command.

; and & have the same precedence, which is lower than && and ||. They allow you to separate commands (;) or run a command in the background (&).

| and |& have higher precedence than &&, ||, ;, and &. They allow you to create pipelines, where the output of one command is used as the input of the next command (|), or where both the output and error output of one command are used as the input of the next command (|&).

( and ) can be used to group commands, which can override the default precedence rules.

;;, ;&, and ;;& are used in the context of a case statement to separate different cases.


The syntax of a programming language is defined by a grammar. The syntax of a programming language is a precise description of all its grammatically correct programs. Noam Chomsky defined four categories of grammars: regular, context-free, context- sensitive, and unrestricted.

How do we write down a grammar that contains an infinite number of valid strings? We obviously can’t list them all out. Instead, we create a finite set of rules.  

![expression_grammar](https://github.com/alx-sch/42_minishell/assets/134595144/60865271-c1f5-49d1-9663-afe2197b123d)



## Lexeme
Our job is to scan through the list of characters and group them together into the smallest sequences that still represent something. Each of these blobs of characters is called a lexeme.
example of lexeme
```
  enum TokenType {
    // Single-character tokens.
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,
    // One or two character tokens.
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,
// Literals.
    IDENTIFIER, STRING, NUMBER,
// Keywords.
    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,
EOF
}
```
To add:

metacharacter
A character that, when unquoted, separates words. A metacharacter is a space, tab, newline, or one of the following characters: ‘|’, ‘&’, ‘;’, ‘(’, ‘)’, ‘<’, or ‘>’.

A token that performs a control function. It is a newline or one of the following: ‘||’, ‘&&’, ‘&’, ‘;’, ‘;;’, ‘;&’, ‘;;&’, ‘|’, ‘|&’, ‘(’, or ‘)’.

A sequence of characters considered a single unit by the shell. It is either a word or an operator.

word
A sequence of characters treated as a unit by the shell. Words may not include unquoted metacharacters.

The core of the scanner is a loop. Starting at the first character of the source code, it figures out what lexeme it belongs to, and consumes it and any following characters that are part of that lexeme. When it reaches the end of that lexeme, it emits a token.

## parsing
In order to evaluate an arithmetic node, you need to know the numeric values of its subtrees, so you have to evaluate those first. That means working your way from the leaves up to the root—a post-order traversal:If I gave you an arithmetic expression, you could draw one of these trees pretty easily.

## context-free grammar (CFG). 
A formal grammar takes a set of atomic pieces it calls its “alphabet”. Then it defines a (usually infinite) set of “strings” that are “in” the grammar. Each string is a sequence of “letters” in the alphabet.

A grammar naturally describes the hierarchical structure of most programming language constructs. For example, an if-else statement in Java can have  
`if (expression) statement else statement`
That is, an if-else statement si the concatenation of the keyword if, an opening parenthesis, an expression, a closing parenthesis, a statement, the keyword else, and another statement. Using the variable expr to denote an expres- sion and the variable stmt to denote a statement, this structuring rule can be expressed as  
`stmt →if (expr) stmt else stmt`

If you start with the rules, you can use them to generate strings that are in the grammar. Strings created this way are called derivations because each is “derived” from the rules of the grammar. In each step of the game, you pick a rule and follow what it tells you to do. Most of the lingo around formal grammars comes from playing them in this direction. Rules are called productions because they produce strings in the grammar.
Each production in a context-free grammar has a head—its name—and a body which describes what it generates. In its pure form, the body is simply a list of symbols. Symbols come in two delectable flavors:
A terminal is a letter from the grammar’s alphabet. You can think of it like a literal value. In the syntactic grammar we’re defining, the terminals are individual lexemes—tokens coming from the scanner like if or 1234.
These are called “terminals”, in the sense of an “end point” because they don’t lead to any further “moves” in the game. You simply produce that one symbol.
A nonterminal is a named reference to another rule in the grammar. It means “play that rule and insert whatever it produces here”. In this way, the grammar composes.

To make this concrete, we need a way to write down these production rules. People have been trying to crystallize grammar all the way back to Pāṇini’s Ashtadhyayi, which codified Sanskrit grammar a mere couple thousand years ago. Not much progress happened until John Backus and company needed a notation for specifying ALGOL 58 and came up with Backus-Naur form.

## functions authorised
### readline
The readline() function is not a standard C library function, but rather a function provided by the GNU Readline library.  

Here's a basic example:
```
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int main() {
    char *input;

    input = readline("Enter some text: ");

    if (input != NULL) {
        printf("You entered: %s\n", input);
		add_history(input); // Add the input to the history list
        free(input); // Free the memory allocated by readline
    }

    return 0;
}

```
need linking with `-lreadline` when compiling.
Using add_history() function, we add the input to the history list maintained by Readline. This allows users to recall and edit previously entered command lines using the up and down arrow keys. It seems that we are not allowed to use the history_list() function or the history_get() function therefore we will have to implement our own history list.

## on the mac m1 
I could get the readline and add_history functions to work on my mac m1. 
But to get the rl_clear_history to work I had to switch libraries. Apparently the readline on the mac is not complete. So using brew I installed the GNU readline and linked it to my project in the makefile using the path found with `brew --prefix readline` which in my system expands to `/opt/homebrew/opt/readline/`.
So my include path and LIBS path look like this:
```
INCLUDES += -I$(shell brew --prefix readline)/include
LDLIBS += -L$(shell brew --prefix readline)/lib  
```

### rl_clear_history
The rl_clear_history function is part of the GNU Readline library, and it is used to clear the history list maintained by Readline. The history list typically stores previously entered command lines, allowing users to recall and edit them.


## structure 
- Phases of the interpreter—scanning, parsing, and
evaluating code.

The first step is scanning, also known as lexing,
A scanner (or lexer) takes in the linear stream of characters and chunks them together into a series of something more akin to “words”. In programming languages, each of these words is called a token. Some tokens are single characters, like ( and , . Others may be several characters long, like numbers ( 123 ), string literals ( "hi!" ), and identifiers ( min )


The next step is parsing. This is where our syntax gets a grammar, the ability to compose larger expressions and statements out of smaller parts.  
A parser takes the flat sequence of tokens and builds a tree structure that mirrors the nested nature of the grammar.  

## What is a shell?

A shell is a program that acts as an interface between the user and the operating system. A shell allows the user to interact with the operating system by accepting commands entered by the user from the keyboard, verifying if the inputs from the user are correct and executing them. Generally, a shell is a user interface that allows us to use computer resources such as memory. Think of a command-line interface such as Bash of Fish. 

Data streams: standard input, output and error

## Interactive and non-interactive shells and scripts

One important aspect to consider when creating a simple shell is whether it is running in interactive mode or non-interactive mode.

In interactive mode, the shell is running in a command line interface and accepts input from the user. This is the mode that most users will be familiar with, and it is important to display a prompt to the user so that they know when the shell is ready to accept input.

In non-interactive mode, the shell is being used to run a script or a batch of commands, and does not accept input from the user. In this mode, there is no need to display a prompt, and the shell should exit once it has executed all the commands in the script.

To check whether the shell is running in interactive mode or non-interactive mode, we can use the isatty() function. This function checks whether a file descriptor refers to a terminal or not. If it returns true, then the shell is running in interactive mode and we should display a prompt. If it returns false, then the shell is running in non-interactive mode and we should not display a prompt.

## Create an infinite loop for the prompt

Once we have determined whether the shell is running in interactive mode or non-interactive mode, we can display a prompt to the user. This input can be a single command or multiple commands separated by a semicolon. To read input from the user, we can use the getline function which reads a line of input from the user. 

## Parse User Input

we will need to read the input from the user and split it into tokens. These tokens can then be analyzed to determine the command the user wants to execute and any arguments or options they have provided. 

## Execute Commands

This involves creating a child process to run the command and using system calls to execute it. To execute the command, we can use the 'execve()' function which executes a command by searching for the executable file in the system’s path environment variable. You will also need to handle any errors that may occur during command execution.  

## Handle the PATH

A path is a list of directories that the shell uses to search for executable files. When a user enters a command in the shell, the shell searches for the corresponding executable file in each directory listed in the path until it finds the executable.

One way to handle paths using a linked list is to create a data structure that stores the directories in the path.  

Once we have the linked list of directories, we can use it to search for executable files when a user enters a command in the shell. 

## Implement Built-In Commands

Built-in commands are special commands that are implemented by the shell itself rather than being external programs. Some common built-in commands include cd, echo, and exit. You will need to implement these commands yourself. Built-in commands such as “cd” or “exit” cannot be executed using the `execve()` function.  

## Support Input/Output Redirection

Input/output redirection allows the user to redirect the input or output of a command to a file instead of the screen or keyboard (standard input or output). To implement I/O redirection, we can use the dup2() function to redirect input or output to a file descriptor.
Redirection operators in Bash are used to control the input and output of commands. They allow you to manipulate where a command reads its input from and where it writes its output to. Here are some common redirection operators:

1. **`>` (Output Redirection):**
   - Redirects the output of a command to a file.
   - Example: `ls > output.txt`
   - This command lists the contents of the current directory and writes the output to a file named `output.txt`.

2. **`<` (Input Redirection):**
   - Takes the input for a command from a file.
   - Example: `sort < input.txt`
   - This command sorts the lines from the file `input.txt`.

3. **`>>` (Append Output):**
   - Appends the output of a command to a file (instead of overwriting it).
   - Example: `echo "new line" >> output.txt`
   - This command appends the text "new line" to the end of the file `output.txt`.

4. **`<<` (Here Document):**
   - Allows you to pass multiple lines of input to a command.
   - Example:
     ```bash
     cat << EOF
     Line 1
     Line 2
     EOF
     ```
     This command uses a here document to pass multiple lines to the `cat` command.

## Support Pipes

To implement pipes, we can use the pipe() function to create a pipe and the fork() function to create a child process for each command.

5. **`|` (Pipe):**
   - Connects the output of one command as the input to another command.
   - Example: `ls | grep "pattern"`
   - This command lists the files in the current directory and pipes the output to `grep` to filter lines containing the specified pattern.

this might not needed in our minishell but leaving it here for completeness:
6. **`2>` and `2>>` (Standard Error Redirection):**
   - Redirects the standard error output of a command to a file (similar to `>` and `>>` for standard output).
   - Example: `command 2> error.log`
   - This command runs `command` and redirects any error messages to a file named `error.

## Support Background Jobs

Background jobs allow a command to be executed in the background, allowing the user to continue working in the shell while the command runs. 
example:
```
$ sleep 10 &
[1] 1234
$ 
```
After entering the command follwed by `&` the shell will display the process id of the background job and the job number.

## ERROR HANDLING

One important aspect of error handling in a shell is checking the return value of system calls and library functions. These calls may fail for various reasons, such as invalid input, insufficient memory, or resource constraints. For example, if the fork() system call fails, it may indicate that the system is out of process resources.

Another aspect of error handling is handling signals. Signals are used by the operating system to notify a process of various events, such as a segmentation fault or a user interrupt. 

Finally, a shell should provide meaningful error messages to the user when a command fails. For example, if the user enters an invalid command, the shell should display an error message indicating that the command is not recognized. Similarly, if a command fails due to a system error, the shell should display an appropriate error message to the user.

Examples of the types of errors that a simple shell may encounter and how they can be handled
ex incorrect command,  incorrect number of arguments, permission denied, system call error, signal handling, memory allocation error, etc.

## Memory Leaks

We use valgrind... On linux.
```
valgrind ./myprogram
```
with flags and options as appropriate.

## It is a huge project - Test the Shell

I have a suite of tests developed for this purpose. Unit tests can be used to test functions and components of the shell, while integration tests can be used to test the shell as a whole.

## bonus
> Your program has to implement:  
	• && and || with parenthesis for priorities.
	• Wildcards * should work for the current working directory.

Some examples of using `&&` (logical AND) and `||` (logical OR) with parentheses for priorities in Bash:

### Using `&&` (Logical AND):

1. **Basic `&&` Example:**
   ```bash
   command1 && command2
   ```
   - If `command1` succeeds (returns a zero exit status), then `command2` will be executed.

2. **Multiple Commands with `&&`:**
   ```bash
   (command1 && command2) && command3
   ```
   - `command1` and `command2` are executed in sequence. If both succeed, then `command3` is executed.

3. **Mixing `&&` and `||`:**
   ```bash
   (command1 && command2) || command3
   ```
   - If `command1` and `command2` succeed, then `command3` will not be executed. If either `command1` or `command2` fails, then `command3` will be executed.

### Using `||` (Logical OR):

1. **Basic `||` Example:**
   ```bash
   command1 || command2
   ```
   - If `command1` fails (returns a non-zero exit status), then `command2` will be executed.

2. **Multiple Commands with `||`:**
   ```bash
   (command1 || command2) || command3
   ```
   - `command1` is executed. If it fails, then `command2` is executed. If both fail, then `command3` is executed.

3. **Mixing `&&` and `||`:**
   ```bash
   (command1 || command2) && command3
   ```
   - If `command1` succeeds, then `command2` will not be executed, and `command3` will be executed. If `command1` fails, then `command2` is executed, and `command3` will not be executed.

Wildcards, such as `*`, are used for pattern matching in file names. Here are some examples of using wildcards in the current working directory:

1. **List all files in the current directory:**
   ```bash
   ls *
   ```
   - This command lists all files (and directories) in the current directory.

2. **Remove all text files in the current directory:**
   ```bash
   rm *.txt
   ```
   - This command removes all files with a `.txt` extension in the current directory.

3. **Copy all `.jpg` files to another directory:**
   ```bash
   cp *.jpg /path/to/destination/
   ```
   - This command copies all files with a `.jpg` extension to the specified destination directory.

4. **Count the lines in all `.log` files:**
   ```bash
   wc -l *.log
   ```
   - This command counts the number of lines in each file with a `.log` extension in the current directory.

5. **Grep for a specific pattern in all `.md` files:**
   ```bash
   grep "pattern" *.md
   ```
   - This command searches for the specified pattern in all files with a `.md` extension.

6. **Archive all `.txt` files into a tarball:**
   ```bash
   tar -cvf archive.tar *.txt
   ```
   - This command creates a tarball (`archive.tar`) containing all files with a `.txt` extension in the current directory.

These examples demonstrate how wildcards can be used in combination with various commands for file manipulation and processing in the current working directory.

## delimiters 
In bash, a delimiter is a character or a set of characters that separates different parts of the command line. The delimiters you've listed are a good start, but bash has a few more. Here's an expanded list:

Space (' ')
Tab ('\t')
Newline ('\n')
Semicolon (';')
Pipe ('|')
Ampersand ('&')
Less than ('<')
Greater than ('>')
Open parenthesis ('(')
Close parenthesis (')')
Open curly brace ('{')
Close curly brace ('}')
Open square bracket ('[')
Close square bracket (']')
Dollar sign ('$')
Backtick (''`)
Double quote ('"')
Single quote ('\'')
Backslash ('\\')
Equals ('=')
Plus ('+')
Minus ('-')
Asterisk ('*')
Slash ('/')
Comma (',')
Exclamation mark ('!')
Tilde ('~')
Caret ('^')
Percent ('%')

## $# means

## {} and [] in bash scripts
they have specific meanings:

{}: Curly braces are used in bash for variable expansion (${variable}), brace expansion ({1..10}), and to define blocks of code (like in if statements and functions).

[]: Square brackets are used in bash for array indexing (array[0]), and to test conditions ([ $a -lt 10 ] or [[ $a -lt 10 ]]).

Here are some examples:

Variable expansion: echo ${variable}
Brace expansion: echo {1..10}

./myscript arg1 arg2 arg3

Then inside myscript, $# will be 3, because three arguments were passed to the script.


The ^ symbol in bash has a few different uses:
1. In regular expressions, ^ is used to denote the start of a line. For example, ^abc matches any line that starts with "abc".
2. In parameter substitution, ${var^} converts the first character of $var to uppercase.
3. In parameter substitution, ${var^^} converts all characters of $var to uppercase.
4. In the tr command, ^ is used to denote a range of characters. For example, tr A-Z a-z converts uppercase letters to lowercase.
5. In the tr command, ^ is used to complement a set of characters when it's the first character in a set. For example, tr -d '^0-9' deletes all characters that are not digits.
6. In the diff command, ^ is used to denote lines that are different between two files.

The <> operator in bash is used for opening a file in read-write mode. Here's an example:

command <> file

This command will run command, with file opened in read-write mode on standard input.



The >&> operator in bash is used for redirection. It redirects both the standard output (stdout) and standard error (stderr) of the command on its left to the file on its right.
Here's an example:
command >&> file
This command will run command, and both the stdout and stderr will be redirected to file.


The >>& operator in bash is used for redirection. It appends the standard output (stdout) and standard error (stderr) of the command on its left to the file on its right.
Here's an example:

command 1>>file 2>&1


This command will run command, and append both the stdout and stderr to file.
Bash 4 and later shortened to
command &>>file


Yes, you can use {} and [] in bash scripts, but they have specific meanings:
* {}: Curly braces are used in bash for variable expansion (${variable}), brace expansion ({1..10}), and to define blocks of code (like in if statements and functions).
* []: Square brackets are used in bash for array indexing (array[0]), and to test conditions ([ $a -lt 10 ] or [[ $a -lt 10 ]]).
Here are some examples:
* Variable expansion: echo ${variable}
* Brace expansion: echo {1..10}
* Code block:```if [ $a -lt 10 ]then  echo "a is less than 10"fi```
* Array indexing: echo ${array[0]}
* Test conditions: if [ $a -lt 10 ] or if [[ $a -lt 10 ]]


No, the symbols ;;, ;&, and ;;& cannot be at the beginning of a command line in bash.
These symbols are used in the context of a case statement in bash scripting:
* ;; is used to end each case in a case statement.
* ;& allows execution to continue with the next case clause, rather than exiting the case statement.
* ;;& allows the shell to test the next pattern list in the case statement.
Here's an example of how they might be used:
```
case "$variable" in
  pattern1)
    command1
    ;;
  pattern2)
    command2
    ;&
  pattern3)
    command3
    ;;&
  *)
    default_command
    ;;
esac

```


```
typedef enum e_tokentype {
    // Control operators
    PIPE, // '|'
    PIPE_AND, // '|&'
    OR_OR, // '||'
    AND_AND, // '&&'
    AND, // '&'
    SEMICOLON, // ';'
    // Grouping commands
    LEFT_PAREN, // '('
    RIGHT_PAREN, // ')'
    // Case statement separators
    SEMICOLON_SEMICOLON, // ';;'
    SEMICOLON_AND, // ';&'
    SEMICOLON_SEMICOLON_AND, // ';;&'
    // Single-character tokens
    LEFT_CURLY, // '{'
    RIGHT_CURLY, // '}'
    COMMA, // ','
    DOT, // '.'
    MINUS, // '-'
    PLUS, // '+'
    SLASH, // '/'
    STAR, // '*'
    QUESTION, // '?'
    COLON, // ':'
    // One or two character tokens
    BANG, // '!'
    BANG_EQUAL, // '!='
    EQUAL, // '='
    EQUAL_EQUAL, // '=='
    GREATER, // '>'
    GREATER_EQUAL, // '>='
    LESS, // '<'
    LESS_EQUAL, // '<='
    // Redirection operators
    REDIRECT_OUT, // '>'
    REDIRECT_IN, // '<'
    APPEND_OUT, // '>>'
    HEREDOC, // '<<'
    REDIRECT_OUT_AND_ERR, // '&>'
    REDIRECT_ERR, // '2>'
    // Command substitution
    COMMAND_SUBSTITUTION, // '$(command)' or '`command`'
    // Literals
    IDENTIFIER, // Any sequence of letters, digits, and underscores
    STRING_TOK, // Any sequence of characters surrounded by quotes
    NUMBER_TOK, // Any sequence of digits
    // Keywords
    IF, THEN, ELSE, ELIF, FI, DO, DONE, WHILE, UNTIL, FOR, CASE, ESAC, SELECT, FUNCTION,
    // Special variables
    DOLLAR_QUESTION, // '$?'
    DOLLAR_DOLLAR, // '$$'
    DOLLAR_STAR, // '$*'
    DOLLAR_AT, // '$@'
    DOLLAR_HASH, // '$#'
    DOLLAR_BANG, // '$!'
} t_tokentype;
```

## control operators
A control operator in bash is one of those ‘||’, ‘&&’, ‘&’, ‘;’, ‘;;’, ‘;&’, ‘;;&’, ‘|’, ‘|&’, ‘(’, or ‘)’

these control operators do have precedence and associativity rules, similar to operators in programming languages. Here's a rough breakdown:
1. && and || have the same precedence and are left-associative. They allow you to execute a command based on the success (&&) or failure (||) of the previous command.
2. ; and & have the same precedence, which is lower than && and ||. They allow you to separate commands (;) or run a command in the background (&).
3. | and |& have higher precedence than &&, ||, ;, and &. They allow you to create pipelines, where the output of one command is used as the input of the next command (|), or where both the output and error output of one command are used as the input of the next command (|&).
4. ( and ) can be used to group commands, which can override the default precedence rules.
5. ;;, ;&, and ;;& are used in the context of a case statement to separate different cases.

## wildcards
For wildcard expansion, you would typically use the glob function, as I mentioned in the previous response. Here's how you can modify your code to expand wildcards in the input:
For example, if a user types ls *.txt, the shell should expand the *.txt wildcard to a list of all .txt files in the current directory.

```
#include <glob.h>

// ...

char *input;
input = readline("minishell $ ");
while (input != NULL)
{
    add_input_to_history(input);

    glob_t glob_result;
    memset(&glob_result, 0, sizeof(glob_result));

    // Expand wildcards in the input
    if (glob(input, GLOB_TILDE, NULL, &glob_result) == 0) {
        for (int i = 0; i < glob_result.gl_pathc; ++i) {
            // Replace the input line with the expanded wildcard
            rl_replace_line(glob_result.gl_pathv[i], 0);
            // Redraw the input line
            rl_redisplay();
        }
    } else {
        ft_printf("You entered: %s\n", input);
    }

    globfree(&glob_result);
    input = readline("minishell $ ");
}

free(input);
```
## ISR? 
The __interrupt and __irq keywords are used in some programming languages and environments to declare interrupt service routines (ISRs). An ISR is a special kind of function that is executed in response to an interrupt signal.
An interrupt is a signal to the processor emitted by hardware or software indicating an event that needs immediate attention. The processor responds by suspending its current activities, saving its state, and executing a function called an interrupt handler (or an interrupt service routine, ISR) to deal with the event. This activity is called "servicing the interrupt."
The __interrupt or __irq keyword is used to tell the compiler that the declared function is an ISR. This can affect the generated code for the function, as ISRs often need to save and restore more processor state than regular functions, and may need special instructions for returning from the function.
The exact details of how the __interrupt or __irq keyword works, and how ISRs are written and work, can depend on the specific programming language, compiler, and hardware you're using.

## input special characters
In a bash shell, you can input a character in hexadecimal using the format $'\xHH', where HH is the hexadecimal value. For example, $'\x04' represents the character with the ASCII value 4.
echo -e "The control character for end of transmission is $'\x04'"
In this command, echo -e enables interpretation of backslash escapes, and $'\x04' is replaced by the character with the ASCII value 4.

In C, you can represent a character in hexadecimal by using the \x escape sequence followed by the hexadecimal value. For example, \x04 represents the character with the ASCII value 4.
If you want to input a character in hexadecimal in your program, you can simply include it in a string or character literal. For example:

char c = '\x04';
char *s = "\x04";

## expansion in bash
In bash, expansion refers to the process of replacing a special character or sequence of characters with a value. There are several types of expansion in bash, including:

- $identifier or ${identifier} is used for variable expansion. The identifier is the name of the variable. Bash replaces $identifier or ${identifier} with the value of the variable.
ex:
```
name="Alice"
echo "Hello, $name"
```

- $(command) or `command` is used for command substitution. The command is a command that Bash will execute, and Bash replaces $(command) or `command` with the output of the command.
ex:
```
echo "The current directory is $(pwd)"
```

- $((expression)) is used for arithmetic expansion. The expression is an arithmetic expression that Bash will evaluate, and Bash replaces $((expression)) with the result of the expression.
ex:
```
echo "The result of 2 + 2 is $((2 + 2))"
```

## expanding with quotes

```
(base)  % cat $"HOME"
cat: $HOME: No such file or directory
(base)  % cat $HOME
cat: /Users/laurentb: Is a directory
(base)  % cat $'HOME'
cat: HOME: No such file or directory
```

Three cases:
- `$"HOME"` : This is used for localized strings in Bash. It's equivalent to `"HOME"` because HOME is not a localized string. So cat $"HOME" tries to display the contents of a file named HOME in the current directory, not your home directory.  
- `$HOME` : This is the correct way to expand the HOME environment variable. It expands to the path of your home directory.
- `$'HOME'` : This is used for string literals in Bash, where escape sequences (like `\n` for newline) are interpreted. Since `HOME` doesn't contain any escape sequences, `$'HOME'` is equivalent to `'HOME'`. So cat `$'HOME'` also tries to display the contents of a file named HOME in the current directory.

## set env variables
If you want to set an environment variable for the new program, you need to use the third argument to `execve()`, which is an array of strings representing the new environment. Each string in this array should be in the format name=value.

```
int main() {
    char *newargv[] = { "/bin/bash", NULL };
    char *newenviron[] = { "MYVAR=2", NULL };

    execve(newargv[0], newargv, newenviron);

    // If execve returns at all, an error occurred.
    perror("execve");
    return 1;
}
```

In this code, newenviron is an array of strings representing the new environment for the new program. The string "MYVAR=2" sets the environment variable MYVAR to 2.
This will start a new bash shell with MYVAR set to 2, but it won't run any command. 
If you want to run a command in the new shell, you can add -c command to newargv, like this:

```
char *newargv[] = { "/bin/bash", "-c", "echo $MYVAR", NULL };
```

In a shell, when you set an environment variable, it's only set for the current shell (the parent process) and any child processes that the shell starts after the variable is set. The environment variable is not passed back to the parent of the shell.

For example, if you start a shell from a terminal, set an environment variable in the shell, and then exit the shell, the environment variable will not be set in the terminal. This is because the terminal is the parent of the shell, and environment variables are not passed from a child process to its parent.

This is why, for example, setting environment variables in a script does not affect the environment of the shell where you run the script. The script runs in a child process, and any environment variables it sets are lost when the script exits.

If you want to set an environment variable in the current shell, you need to use the export command in the shell itself, not in a child process. If you want to set an environment variable for all shells, you can add the export command to a shell startup file like `~/.bashrc` or `~/.bash_profile`.

## Quotes

In the context of shell scripting, single quotes (') and double quotes (") have different behaviors:  

- Single Quotes ('): Anything enclosed between single quotes is preserved exactly as typed. No variable substitution or command substitution will occur within single quotes. For example, if you have a variable var="world" and you echo 'Hello $var', it will output Hello $var, not Hello world.

- Double Quotes ("): Within double quotes, variable substitution and command substitution will occur. For example, if you have a variable var="world" and you echo "Hello $var", it will output Hello world. Similarly, if you echo "Today is $(date)", it will replace $(date) with the current date.  

In the context of shell scripting, the echo command is used to output text. The text to be output is enclosed in quotes.
In your command echo " Hello' $var'", you're using a mix of double quotes (") and single quotes ('). Here's how it works:

```
echo " Hello '$var' ! "
```

The double quotes (") start at the beginning and end at the end of the string. Within double quotes, variable substitution will occur. This means that $var will be replaced with the value of the variable var.

The single quotes (') are treated as literal characters within the double quotes. They do not start a new quoted string, and they do not prevent variable substitution. So ' $var' is not treated as a single-quoted string; instead, it's part of the double-quoted string.

So, if var="world", your command will output Hello' world'.

## redirections
Bash does handle redirections without a command. It's just that there's no command to execute, so nothing will be written to/read from the redirections.
Regarding the problematic case, heredocs should (preferably) be handled during or right after parsing.
Look at these cases in bash:

### case 1 (no syntax error):
```
<<1 cat | <<2 cat | ( <<3 cat | <<4 cat || <<5 cat | ( <<6 cat ) && <<7 cat ) | <<8 cat <<9 | <<10 cat
```
### case 2 (syntax error):
```<<1 cat | <<2 cat | ( <<3 cat | <<4 cat || <<5 cat | ( <<6 cat ) && <<7 cat ) | () <<8 cat <<9 | <<10 cat```
### case 3 (syntax error):
```
<<1 cat | <<2 cat | ( <<3 cat | <<4 cat || <<5 cat | ( <<6 cat ) && <<7 cat ) | <<8 () cat <<9 | <<10 cat
```
### case 4 (syntax error):
```
<<1 cat | <<2 cat | ( <<3 cat | <<4 cat || <<5 cat | ( <<6 cat ) && <<7 cat ) | <<8 cat <<9 () | <<10 cat
```
In the first case, you can press CTRL+D 10 times, no error, heredocs are handles left-to-right.
In the second case, you'll get a syntax error as soon as you press enter.
In the third case, you can press CTRL+D until heredoc #8 is handled, afterwards you'll get a syntax error.
In the fourth case, you can press CTRL+D until heredoc #9 is handled, afterwards you'll get a syntax error.
Of course, the cat commands could've been left out, but i kept them for clarity.
Now, of course you don't have to handle it like bash, but bash shows a good way to handle heredocs. (edited) 

## environmental and local variables
In Bash, when you create a variable using the var="heyhey" syntax, you're creating a shell variable. Shell variables are only available in the current shell (i.e., the current terminal session). They are not passed to child processes (i.e., commands or scripts that you run from the current shell).

If you want to make a shell variable available to child processes, you need to export it as an environment variable using the export command. For example:
```
var="heyhey"
export var
```
After this, var is an environment variable, and it will be passed to child processes. You can also do this in one line:

```
export var="heyhey"
```
To see the difference between shell variables and environment variables, you can run the following commands:
```
var="heyhey"
echo $var
bash -c 'echo $var'
export var="heyhey"
bash -c 'echo $var'
```
The first command will print heyhey, the second will print an empty line, the third will print heyhey, and the fourth will print heyhey.
In our shell implementation, you would need to handle these two types of variables separately. 

Shell variables can be stored in a local data structure, while environment variables can be stored in the environ global variable or managed using the getenv, setenv, and unsetenv functions.

## HEREDOC
In Bash scripting, a here document (heredoc) is a type of redirection that allows to pass a block of input to a command. The syntax for a heredoc is as follows (, in Backus–Naur form):
```
command <<DELIMITER
text block
DELIMITER
```
Here's how it works:
- command is the command that will receive the text block as input.  
- `<<` DELIMITER starts the heredoc. DELIMITER can be any string. It marks the beginning and the end of the text block.  
- text block is the input that will be passed to the command. It can be multiple lines.  
- DELIMITER on a line by itself ends the heredoc.  

Here's an example:
```
command <<DELIMITER
text block
DELIMITER
```

This will pass the two lines of text to the cat command, which will print them.  

In our parser, we would need to handle heredocs as a special case of redirection. When we encounter a `<<DELIMITER`, we would need to read lines until you encounter a line that contains only `DELIMITER`. The lines in between become the input for the command.

The heredoc syntax in a grammar could be represented as follows:
```
heredoc -> 	expression "<<" delimiter NEWLINE content delimiter NEWLINE;
```
The heredoc -> expression "<<" delimiter NEWLINE content delimiter NEWLINE; rule correctly captures the structure of a heredoc, where:

expression is the command that will receive the heredoc as input.
"<<" is the heredoc operator.
delimiter is the string that marks the beginning and end of the heredoc.
NEWLINE separates the delimiter from the content of the heredoc and the content from the ending delimiter.
content is the text of the heredoc.
The expression before "<<" in the heredoc rule ensures that a heredoc is associated with a command, which is necessary because a heredoc is a form of input redirection.
## Execute a shell command
Use fork() to create a new process, and then use `execve()` in the child process to replace it with a shell that executes the command. Here's an example:
```
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        // Handle error
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // Child process
        char *argv[] = { "/bin/sh", "-c", "ls -l", NULL };
        execve(argv[0], argv, NULL);

        // If execve returns at all, an error occurred.
        perror("execve");
        return 1;
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
        // The child process has finished executing the command.
    }
    return 0;
}
```

## see the exit status of the last command.
```
echo $?
```
# Functions allowed:

### Handling input:

**readline**

`char *readline(const char *prompt);`

- Reads a line from the terminal and returns it.
- Basically waiting for input (something written in the terminal), and then returning it.
- Prompt is what is being output in the terminal, and the char * return is what is being input from the terminal.

**rl_clear_history**

`void rl_clear_history(void);`

- Used to clear the history of previously entered command lines stored by the Readline library.

**rl_on_new_line**

`void rl_on_new_line(void);`

- Used to notify the Readline library that the cursor has moved to a new line.
- In interactive command-line programs, the cursor position is important for proper line editing and display. This function ensures that Readline is aware of the cursor's position when a new line is started.

**rl_replace_line**

`int rl_replace_line(const char *text, int clear_undo);`

- Replaces the current input line in the Readline library's line buffer with a new line.
- It allows you to update or modify the current input line being edited by Readline, providing flexibility for interactive command-line interfaces.
- No return value.
- For instance: Autocompletion of a command by pressing tab.

**rl_redisplay**

`void rl_redisplay(void);`

- Displays the new line from rl_replace_line.
- No return value.

**add_history**

`void add_history(const char *line);`

- Takes a string as an argument and adds it to the history list of input lines.
- So when you go up and down with the arrows, you can see the history of inputs.

### Handling file descriptors:

**access**

`int access(const char *pathname, int mode);`

- Checks if the file is accessible.
- `F_OK`: tests for the existence of the file.
- `R_OK`: tests for read permission.
- `W_OK`: tests for write permission.
- `X_OK`: tests for execute (search) permission.

**open**

`int open(const char *pathname, int flags, mode_t mode);`

The `flags` argument in the `open` function controls how the file should be accessed. Here are some commonly used flags:

- `O_RDONLY`: Open for reading only.
- `O_WRONLY`: Open for writing only.
- `O_RDWR`: Open for reading and writing.
- `O_CREAT`: Create file if it does not exist.
- `O_TRUNC`: Truncate file to zero length.
- `O_APPEND`: If set, the file offset shall be set to the end of the file prior to each write.

These flags can be combined using the bitwise OR operator.

The `mode` argument is only used when the `O_CREAT` flag is used, and it specifies the permissions to use in case a new 
file is created. This is a number, typically specified in octal. For example, a mode of `0644` stands for owner read/write, group and others read only.

**read**

`ssize_t read(int fd, void *buf, size_t count);`

The `read` function is a system call in Unix-like operating systems that reads 
data from a file descriptor into a buffer. Here's a brief explanation of its parameters:

- `int fd`: This is the file descriptor from which to read. It's usually obtained from the `open` system call.
- `void *buf`: This is a pointer to the buffer where the read data will be stored.
- `size_t count`: This is the number of bytes to read.

The function returns the number of bytes read on success, 0 on end of file, and -1 on error.

**close**

`int close(int fd);`

The `close` function is a system call used to close a file descriptor. Here's a brief explanation of its parameter:

- `int fd`: This is the file descriptor to be closed. It's usually obtained from the `open` system call.

The function returns 0 on success and -1 on error. After a file descriptor has been closed, it can no longer be used to read or write data. The system resources associated with the file descriptor are freed.

### Handling processes:

**fork**

`pid_t fork(void);`

The `fork` function is a system call used to create a new process. 

When a process calls `fork`, it creates a new process called a **child process**. 

—> The child process is an exact copy of the    calling process, known as the parent process, 
except for a few values that get changed, such as the process ID.

Here's a brief explanation of its usage:

- The function doesn't take any parameters.
- It returns the process ID of the child process if you’re in the parent process.
- It returns 0 if you’re inside a child process.
- If the fork fails, it returns -1.

Remember, after a `fork`, both the parent and child processes will execute the next instruction following the `fork` call. So, you'll often see a check for the fork's return value to differentiate the code executed by the parent and the child.

**wait**

`pid_t wait(int *status);`

- This function makes the parent process wait until one of its child processes exits.
- The exit status of the child is stored in the integer pointed to by `status`.
- If `status` is NULL, no status information is saved.
- The function returns the process ID of the 
child that exited, or -1 if an error occurred.

**waitpid**

`pid_t waitpid(pid_t pid, int *status, int options);`

- This function is a more flexible version of `wait`.
- It waits for a specific child process to exit, as specified by `pid`.
- The `options` parameter can modify the behavior of `waitpid`.
- For example, setting options to `WNOHANG` causes `waitpid` to return immediately instead of waiting, if no child specified by `pid` has exited yet.
- Like `wait`, `waitpid` saves the exit status of the child in `status` and returns the process ID of the child that exited, or -1 if an error occurred.

**wait3**

`pid_t wait3(int *status, int options, struct rusage *rusage);`

- This function waits for a child process to stop or terminate.
- It also returns resource usage statistics for the child in a `struct rusage` that's passed as an argument.

**wait4**

`pid_t wait4(pid_t pid, int *status, int options, struct rusage *rusage);`

- This function is similar to `wait3`, but it allows you to wait for a specific child process to stop or terminate.

<aside>
💡 The `struct rusage` is a structure used to return resource usage statistics.

It's defined in the `sys/resource.h` header file in Unix-like operating systems. 

This structure includes information such as the amount of CPU time used, the amount of shared and unshared memory used, the number of page faults, and so on.

Each `struct timeval` itself is a structure that represents time, with fields for seconds and microseconds.

</aside>

### Handling signals:

**signal**

`int signal(int signum, sighandler_t handler);`

- This function sets a function to handle a signal.
- `signum` is the signal number and `handler` is a pointer to the function that will handle the signal.
- The function returns 0 on success and -1 on error.

**sigaction**

`int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);`

- This function is used to change the action taken by a process on receipt of a specific signal.
- `signum` specifies the signal and `act` specifies the new action for the signal.
- `oldact` is used to save the previous action.

**sigemptyset**

`int sigemptyset(sigset_t *set);`

- This function initializes a signal set to empty.
- `set` is a pointer to the signal set to initialize.
- The function returns 0 on success and -1 on error.

**sigaddset**

`int sigaddset(sigset_t *set, int signum);`

- This function adds a signal to a signal set.
- `set` is a pointer to the signal set and `signum` is the signal to add.
- The function returns 0 on success and -1 on error.

**kill**

`int kill(pid_t pid, int sig);`

- This function sends a signal to a process or a group of processes.
- `pid` is the process ID and `sig` is the signal to send.
- The function returns 0 on success and -1 on error.

**exit**

`exit(int status)`

- This function terminates the calling process immediately.
- Any open file descriptors belonging to the process are closed and any children of the process are inherited by process 1, init, and the process's parent is sent a SIGCHLD signal.

### Handling directories:

**getcwd**

`getcwd(char *buf, size_t size)`

- This function gets the current working directory of the process and puts it in `buf`.
- The `size` argument specifies the size of the `buf` array.
- **Works like pwd-command.**

**chdir**

`chdir(const char *path)`

- This function changes the current working directory of the calling process to the directory specified in `path`.
- **Works like cd-command.**

**opendir**

`opendir(const char *name)`

- This function opens a directory stream corresponding to the directory 
name, and returns a pointer to the directory stream.
- The stream is positioned at the first entry in the directory.

**readdir**

`readdir(DIR *dirp)`

- This function returns a pointer to a dirent structure representing the 
next directory entry in the directory stream pointed to by `dirp`.
- It returns NULL on reaching the end of the directory stream or if an error occurred.

**closedir**

`closedir(DIR *dirp)`

- This function closes the directory stream associated with `dirp`.
- A successful call to `closedir()` also closes the underlying file descriptor associated with `dirp`.

### Handling files:

**stat**

`stat(const char *restrict path, struct stat *restrict buf)`

- This function returns information about a file.
- `path` points to the pathname of the file.
- `buf` is a pointer to a `stat` structure where status information about the file is stored.
- **You could use this function to retrieve information about a file, such as its size, permissions, and modification time.**

**lstat**

`lstat(const char *restrict path, struct stat *restrict buf)`

- Similar to `stat()`, but if `path` is a symbolic link, then it returns information about the link itself, not the file that it refers to.
- **This could be useful for implementing commands that need to handle symbolic links differently from regular files.**

**fstat**

`fstat(int fd, struct stat *buf)`

- Similar to `stat()`, but takes a file descriptor `fd` instead of a path.
- It returns information about the file that is currently opened by `fd`.
- **This could be useful for commands that work with file 
descriptors, such as redirection operators (`>`, `<`, `>>`, etc.).**

**unlink**

`unlink(const char *pathname)`

- This function deletes a name from the filesystem.
- If that name was the last link to a file and no processes have the file open, the file is deleted and the space it was using is made available for reuse.

### Handling piping, redirection and execution:

**execve**

`execve(const char *filename, char *const argv[], char *const envp[])`

- This function replaces the current process image with a new process image specified by `filename`.
- The `argv` is an array of argument strings passed to the new program.
- `envp` is an array of strings, conventionally of the form `key=value`, which are passed as environment to the new program.
- **Essentially running one of the standard commands which are stored as executables in the computer’s file system.**

**dup**

`dup(int oldfd)`

- This function creates a copy of the file descriptor `oldfd`.
- The new file descriptor returned by the function is the lowest-numbered file descriptor not currently open for the process.

**dup2**

`dup2(int oldfd, int newfd)`

- This function also creates a copy of the file descriptor `oldfd`, but it uses the descriptor number specified by `newfd`.
- If `newfd` was previously open, it is silently closed before being reused.

**pipe**

`pipe(int pipefd[2])`

- This function creates a pipe, a unidirectional data channel that can be used for interprocess communication.
- The array `pipefd` is used to return two file descriptors referring to the ends of the pipe.
- `pipefd[0]` refers to the read end, `pipefd[1]` to the write end.

### Handling errors:

**strerror**
`char *strerror(int errnum);`

- This function returns a pointer to a string that describes the error code passed in the argument.
- The integer you pass to `strerror`is typically an error number that you've received from a previous system or library call that failed.
- In C, this is often obtained from the global variable `errno`. When a system call fails, it usually sets `errno` to a value that indicates what the error was.
- You can then pass this value to `strerror` to get a human-readable string that describes the error.

**perror**
`void perror(const char *str);`

- This function produces a message on the standard error output, 
describing the last error encountered during a call to a system or 
library function.
- In the case of `perror`, the `str` argument points to a string that you would like to be output before the error message itself.
- This can be useful for specifying where in your code the error occurred.

### Handling terminal/environment:

**isatty**
`int isatty(int fd);`

- This function is used to determine if a file descriptor refers to a 
terminal. It returns 1 if the descriptor is a terminal, otherwise it 
returns 0.
- For example, you might use this to check if your program's 
output is being redirected to a file or if it's being displayed on the 
terminal.

**ttyname**
`char *ttyname(int fd);`

- This function returns the name of the terminal associated with a given 
file descriptor.
- For example, it might return "/dev/tty1" if your program is running in the first virtual console.

**ttyslot**
`int ttyslot(void);`

- This function is used to find the terminal slot number for the current user.
- This is a somewhat outdated concept from the days of multi-user mainframe computers, and isn't commonly used in modern programming.

**ioctl**
`int ioctl(int fd, unsigned long request, ...);`

- This is a very general function used for device-specific input/output 
controls.
- It's used for a wide variety of tasks, such as setting the 
baud rate for a serial port, or controlling the brightness of a display.
- The exact parameters and behavior depend on the device you're 
controlling.

**getenv**
`char *getenv(const char *name);`

- This function searches the environment list to find the environment variable which matches the string pointed to by `name`, and returns a pointer to the corresponding value string.

**tcsetattr**

`int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);`

- This function is used to set the terminal attributes for the terminal 
referred to by the given file descriptor.
- In a shell, you might use this to change terminal settings like echo mode or canonical mode.
- In a terminal, "echo mode" and "canonical mode" are settings that control how input and output are handled.
- **Echo mode** determines whether the characters you type are displayed on the terminal.
    
    —> When echo mode is on, anything you type will be displayed.
    
    —> When it's off, nothing is displayed when you type. 
    
    —> This is useful, for example, when a program is asking for a password and you don't want the password to be displayed on the screen.
    
- **Canonical mode**, also known as "cooked" mode, allows the terminal to process input line by line.
    
    —> When canonical mode is on, the terminal will buffer the characters you type until you press Enter, at which point 
    the entire line is sent to the program. 
    
    —> When canonical mode is off, also known as "raw" mode, characters are sent to the program as soon as they're typed. This is useful for programs that need to handle interactive input, like a text editor. **And also for the auto-completion maybe, when you press tab, and it auto-finishes the command or path?**
    

**In a shell program, you might use `tcsetattr` to switch 
between these modes depending on what the program is doing. For example,you might turn off echo mode when asking for a password, or switch to raw mode when running a text editor.**

**tcgetattr**

`int tcgetattr(int fd, struct termios *termios_p);`

- This function gets the current terminal attributes for the terminal 
referred to by the given file descriptor.
- In a shell, you might use this to save the current terminal settings so you can restore them later.

**tcgetent**

`int tgetent(char *bp, const char *name);`

- This function is used to get an entry for terminal name in buffer bp 
from the termcap database.
- In a shell, you might use this to get information about the capabilities of the terminal.

**tgetflag**

`int tgetflag(char *id);`

- This function gets the boolean entry for id from the termcap database.
- In a shell, you might use this to check if the terminal supports a 
certain feature.

**tgetnum**

`int tgetnum(char *id);`

- This function gets the numeric entry for id from the termcap database.
- In a shell, you might use this to get numeric information about the 
terminal, like its size.

**tgetstr**

`char *tgetstr(char *id, char **area);`

- This function gets the string entry for id from the termcap database.
- In a shell, you might use this to get string information about the 
terminal, like the sequence to clear the screen.

**tgoto**

`char *tgoto(const char *cap, int col, int row);` 

- This function decodes a cursor motion string.
- In a shell, you might use this to move the cursor around the screen.

**tputs**

`int tputs(const char *str, int affcnt, int (*putc)(int));`

- This function applies padding information to a string and outputs it.
- In a shell, you might use this to output control sequences to the 
terminal.

<aside>
💡 **What is a “token” in programming?**

Imagine building something with Lego bricks. Each brick is like a token in programming. There are five types of these "bricks":

- Constants: These are like the fixed pieces, never changing.
- Identifiers: They're like names you give to certain things, like labeling your Lego creations.
- Operators: These are like the tools you use to manipulate the bricks, like adding or subtracting.
- Separators: They're like the spaces or borders between different parts of your Lego creation.
- Reserved Words: These are special words that have specific meanings in the programming language you're using, kind of like special instructions.
</aside>

## links
The Bash reference manual:  
https://www.gnu.org/software/bash/manual/bash.html  
the canonical reference for all things compiler:  
Compilers: Principles, Techniques, and Tools (universally known as “the Dragon Book”) .  
Another compiler book. There is a nice explanation of creating a AST or syntax tree
https://craftinginterpreters.com
Also the web version is freely available:  
https://craftinginterpreters.com/parsing-expressions.html  

This is an important concept about grammar:  
https://en.wikipedia.org/wiki/Backus–Naur_form  

This is from a programming book - Implement your own shell - GustavoRodriguez-RiveraandJustinEnnen  
https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf  
some blog posts:  

Tutorial - Write a Shell in C - Stephen Brennan  
https://brennan.io/2015/01/16/write-a-shell-in-c/  
https://medium.com/@winfrednginakilonzo/guide-to-code-a-simple-shell-in-c-bd4a3a4c41cd   
https://www.peroxide.dk/download/tutorials/pxdscript/chapter1.html  
