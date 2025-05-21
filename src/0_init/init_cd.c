#include "minishell.h"

// IN FILE:

void	init_cd_struct(t_cd **cd);

// Initializes the cd-struct (built-in).
void	init_cd_struct(t_cd **cd)
{
	*cd = malloc(sizeof(t_cd));
	if (!(*cd))
		print_error_cd(1, cd);
	(*cd)->home_user = NULL;
	(*cd)->parentdirectory = NULL;
	(*cd)->subdirectory = NULL;
}
