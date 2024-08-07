/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:09:56 by aschenk           #+#    #+#             */
/*   Updated: 2024/08/07 18:51:26 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
Declarations for built-in minishell commands and their utility functions:
`cd`, `pwd`, `env`, `unset`, `export`, and `echo`.
*/

#ifndef BUILTINS_H
# define BUILTINS_H

# include <stdbool.h> // bool
# include "types.h"

// Builtins:

int				is_parent_builtin(t_exec *exec);
int				is_builtin(t_exec *exec);
int				builtin(t_data *data, t_exec *exec);
int				cd(t_data *data, t_exec *exec);
int				pwd(t_exec *exec);
int				env(t_exec *exec, t_env *env_temp);
int				unset(t_exec *exec, t_env **envp_temp);
int				is_exit(t_data *data, t_exec *exec);
unsigned int	exit_with_code(t_data *data, t_exec *exec);
int				export(t_data *data, t_exec *exec);
int				minishell_echo(t_exec *exec);

// Butiltins utils:

void			add_env_var_no_value(t_data *data, char *arg);
void			add_env_var_export_with_value(t_data *data, char *arg);
void			add_env_var_envp_with_value(t_data *data, char *arg);
void			ft_env_tmp_add_back(t_env **head, t_env *new);
int				count_array_length(char **array);

// Modified standard functions:

int				ft_strchr_index(const char *s, int c);
int				ft_strrchr_index(const char *s, int c);
bool			is_only_duplicates(char *s, char c);
int				is_letter(char c);
int				ft_is_alphanumerical(char **str);

// Errors:

int				print_error_cd(int error_code, t_cd **cd);
void			print_error_exit(t_data *data, t_exec *exec);
int				env_error_messages(char *input, int i);
void			mem_alloc_fail_env(t_env **head);
void			exit_check_argc(t_data *data);
int				export_err_invalid_option(char *input, int i);
void			unset_err_memalloc_fail(t_env **envp_temp);
int				unset_err_invalid_option(char *input, int i);
int				pwd_invalid_option(char *input, int i);
void			export_mem_alloc_failure(t_data *data);

// Freeing allocated memory for builtins:

int				ft_freearray(char **arr);
int				too_many_args_cd(t_cd **cd);
int				free_cd_struct(t_cd **cd, int exit_status);
void			free_env_struct(t_env **head);

#endif
