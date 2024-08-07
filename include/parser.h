/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:57:57 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/07 13:35:22 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
This header file defines functions for parsing and processing tokens generated
by the tokenizer. It includes functionalities for handling various aspects of the
shell's input, such as managing here-documents, performing variable expansions,
and counting pipes.

The parsing process prepares the tokens for execution by organizing and
transforming them into a structured format suitable for further processing
by the shell.
*/

#ifndef PARSER_H
# define PARSER_H

# include "types.h"

// 2_parser/parser.c

int		parse_tokens(t_data *data);

// 2_parser/parser_heredoc.c

int		process_heredocs(t_data *data);

// 2_parser/parser_heredoc_utils.c

void	count_pipes(t_data *data, t_token *node);
void	trim_newline(char *str);
char	*get_heredoc(t_data *data);
int		get_heredoc_fd(t_data *data);
char	*trim_delimiter(const char *delimiter);

// 2_parser/parser_var_expansion.c

int		expand_variables(char **str, t_data *data);
int		expand_variables_selective(char **str, t_data *data);

// 2_parser/parser_var_expansion_utils.c

int		get_str_l(char **str, int i, char **substr_left);
int		get_str_r(char **str, int i, char *var_name, char **substr_right);
int		join_str_l(char **str, char *str_l, char *var_value);
int		join_str_r(char **str, char *str_r);
void	free_vars(char **var_val, char **str_l, char **str_r);

#endif
