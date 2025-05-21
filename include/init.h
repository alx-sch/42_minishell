/**
Contains declarations for functions that initialize various data structures
used throughout the project, as defined in types.h.
*/

#ifndef INIT_H
# define INIT_H

# include "types.h"

void	print_logo(void);
void	init_data_struct(t_data *data, int argc, char **argv, char **envp);
void	init_cd_struct(t_cd **cd);
t_env	*init_env_tmp(char **envp);
t_env	*init_export_list(t_data *data);

#endif
