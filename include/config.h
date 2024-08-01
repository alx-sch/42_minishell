/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:54:03 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/01 06:22:13 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This header file defines configuration constants and ANSI escape codes, e.g.
used for terminal formatting, prompt definitions, history configurations etc.
*/

#ifndef CONFIG_H
# define CONFIG_H

// Define ANSI escape codes for colors and styles
# define RESET			"\033[0m"
# define BOLD			"\033[1m"
# define RED			"\033[31;2m"
# define GREEN			"\033[32m"
# define YELLOW			"\033[33m"
# define L_RED			"\033[91m"
# define ORANGE			"\033[38;5;208m"
# define BLUE 			"\033[34m"
# define VIOLET 		"\033[35;1m"

# define PROMPT			"🌈\033[38;5;208m\033[1m minishell$ \033[0m"
# define HEREDOC_P		"> "

// History: Override macros when invoking 'make':
// 'make CFLAGS+="-DHIST_FILE='new_path' -DHIST_SIZE=42"
# define HIST_FILE		"/.minishell_history"
# define HIST_SIZE		1000

# define HEREDOC_PREFIX	".heredoc_"

# define MAX_VAR_NAME	1024

#endif
