/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:30:48 by aschenk           #+#    #+#             */
/*   Updated: 2024/07/31 18:37:02 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
Contains declarations for functions that initialize various data structures
used throughout the project, as defined in types.h.
*/

#ifndef INIT_H
# define INIT_H

# include "types.h"

void	init_data_struct(t_data *data, int argc, char **argv, char **envp);
void	init_cd_struct(t_cd **cd, char *input);
t_env	*init_env_tmp(char **envp);
t_env	*init_export_list(t_data *data);

#endif