/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:57:57 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/12 20:33:12 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
WIP
*/
typedef struct s_heredoc
{
	t_token_type	type;
	char			*lexeme;
	int				position;
}	t_heredoc;
