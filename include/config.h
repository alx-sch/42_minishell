/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:54:03 by aschenk           #+#    #+#             */
/*   Updated: 2024/05/25 00:56:19 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# define PROMPT			"minishell🌈$ "
# define ERR_PREFIX		"minishell: "

// History: Override macros when invoking 'make':
// 'make CFLAGS+="-DHIST_FILE='new_path' -DHIST_SIZE=42"
# define HIST_FILE	"/.minishell_history"
# define HIST_SIZE	1000

# define MAX_VAR_NAME	1024

#endif
