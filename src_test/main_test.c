/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aschenk <aschenk@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:05:14 by aschenk           #+#    #+#             */
/*   Updated: 2024/05/06 18:23:42 by aschenk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
main is first of all a loop that runs the shell taking inputs from the user
and executing them until the user decides to exit it.  
*/
int	main(int argc, char **argv)
{
	argc = 0;
	argv = NULL;

	printf("YAY MINISHELL!\n");
	printf("DEBUG MODE!\n");
	exit(EXIT_SUCCESS);
}
