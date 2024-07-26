/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:57:57 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/26 18:11:48 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
TBD
*/

#ifndef PARSER_H
# define PARSER_H

// 2_parser/parser.c

int		parse_tokens(t_data *data);

// 2_parser/parser_heredoc.c

int		process_heredocs(t_data *data);

// 2_parser/parser_heredoc_utils.c

void	count_pipes(t_data *data, t_token *node);
void	trim_newline(char *str);
char	*get_heredoc(t_data *data);
int		get_heredoc_fd(t_data *data);

#endif
