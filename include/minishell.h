/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:08:35 by aschenk           #+#    #+#             */
/*   Updated: 2024/05/14 17:38:30 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "settings.h" // prompt, etc.
# include "libft.h" // libft

# include <stdlib.h> // malloc, free, exit
# include <fcntl.h> // open, close, read, write, access, unlink
# include <stdio.h> // perror, printf
# include <string.h> // strerror
# include <errno.h> // errno
# include <unistd.h> // fork, pipe, execve, macros like 'STDERR_FILENO' etc.
# include <sys/wait.h> // waitpid
# include <sys/stat.h> // stat, lstat, fstat
# include <sys/ioctl.h> // ioctl
# include <readline/readline.h> // reading/editing input lines
# include <readline/history.h> // tracking/accessing previous command lines
# include <signal.h> // signal/sig fcts, kill
# include <dirent.h> // opendir, readdir, closedir
# include <termios.h> // tcsetattr, tcgetattr
# include <curses.h> // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

// History: Override macros when invoking 'make:
// 'make C#endifFLAGS+="-DHIST_FILE='new_path' -DHIST_SIZE=42"
# define HIST_PATH	"/.minishell_history"
# define HIST_SIZE	1000

typedef struct s_cd
{
	char	*username;
	char	*subdirectory;
	char	*home_user;
	char	*parentdirectory;
	char	**component;
}	t_cd;

// Parsing:
void	parsing(char *input, char **envp);

// Builtins:
void	init_cd_struct(t_cd **cd, char *input);
void	cd(char *input, char **envp);
void	pwd(void);

// Modified standard functions:
int		ft_strrchr_index(const char *s, int c);

// Counting-functions:
int		count_array_length(char **array);

// Freeing allocated memory:
int		ft_freearray(char **arr);
void	free_cd_struct(t_cd **cd);

// Errors:
void	print_error_cd(int error_code, t_cd **cd);

#endif
