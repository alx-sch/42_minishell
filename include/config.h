/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:54:03 by aschenk           #+#    #+#             */
/*   Updated: 2024/11/29 13:38:30 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This header file defines configuration constants and ANSI escape codes, e.g.
used for terminal formatting, prompt definitions, history configurations etc.
*/

#ifndef CONFIG_H
# define CONFIG_H

// Define ANSI escape codes for colors and styles;
// incl.escape sequences for marking non-printable characters (\001 and \002).
# define RESET		"\001\033[0m\002"
# define BOLD		"\001\033[1m\002"
# define RED		"\001\033[31;2m\002"
# define GREEN		"\001\033[32m\002"
# define YELLOW		"\001\033[33m\002"
# define L_RED		"\001\033[91m\002"
# define ORANGE		"\001\033[38;5;208m\002"
# define BLUE 		"\001\033[34m\002"
# define VIOLET 	"\001\033[35;1m\002"

# define PROMPT		"\001\033[1m\033[38;5;208m\002🌈 minishell$ \001\033[0m\002"
# define HEREDOC_P	"> "

// History: Override macros when invoking 'make':
// 'make CFLAGS+="-DHIST_FILE='new_path' -DHIST_SIZE=42"
# define HIST_FILE		".minishell_history"

# define HEREDOC_PREFIX	".heredoc_"

# define MAX_BUFFER		1024

#endif
