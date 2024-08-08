/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:57:57 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/08 19:22:37 by aschenk          ###   ########.fr       */
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

// 2_parser/parser_utils.c

bool	process_quote(char ch, bool *in_single_quote, bool *in_double_quote);
char	*trim_paired_quotes(const char *str);
int		is_variable(char *str, int i);
void	count_pipes(t_data *data, t_token *node);

// 2_parser/parser_heredoc.c

int		process_heredocs(t_data *data);

// 2_parser/parser_heredoc_utils.c

void	trim_newline(char *str);
char	*get_heredoc(t_data *data);
int		get_heredoc_fd(t_data *data);
int		convert_tokens(t_data *data, t_token *curr_token, t_token *next_token);

// 2_parser/parser_var_expansion.c

int		expand_variables(char **str, t_data *data, int expand_in_single_quotes);

// 2_parser/parser_var_expansion_utils.c

int		get_str_l(char **str, int i, char **substr_left);
int		get_str_r(char **str, int i, char *var_name, char **substr_right);
int		join_str_l(char **str, char *str_l, char *var_value);
int		join_str_r(char **str, char *str_r);
void	free_vars(char **var_val, char **str_l, char **str_r);

#endif
