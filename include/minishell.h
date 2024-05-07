/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:08:35 by aschenk           #+#    #+#             */
/*   Updated: 2024/05/06 18:13:45 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
// 'make CFLAGS+="-DHIST_FILE='new_path' -DHIST_SIZE=42"
# define HIST_PATH	"/.minishell_history"
# define HIST_SIZE	1000

#endif
