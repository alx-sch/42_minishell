/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logo_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nholbroo <nholbroo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 14:25:03 by nholbroo          #+#    #+#             */
/*   Updated: 2024/08/08 14:25:14 by nholbroo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Prints a custom, color-coded logo for the minishell project.
void	print_logo(void)
{
	printf("%s%s _  _   ", BOLD, L_RED);
	printf("%s__   %s__ _   ", ORANGE, YELLOW);
	printf("%s__   %s____   ", GREEN, BLUE);
	printf("%s_  _   %s____   ", VIOLET, L_RED);
	printf("%s__     %s__   \n", ORANGE, YELLOW);
	printf("%s( \\/ ) %s(  ) ", L_RED, ORANGE);
	printf("%s(  ( \\ %s(  ) ", YELLOW, GREEN);
	printf("%s/ ___) %s/ )( \\ ", BLUE, VIOLET);
	printf("%s(  __) %s(  )   ", L_RED, ORANGE);
	printf("%s(  )  \n", YELLOW);
	printf("%s/ \\/ \\  %s)(  ", L_RED, ORANGE);
	printf("%s/    /  %s)(  ", YELLOW, GREEN);
	printf("%s\\___ \\ %s) __ (  ", BLUE, VIOLET);
	printf("%s) _)  %s/ (_/\\ ", L_RED, ORANGE);
	printf("%s/ (_/\\ \n", YELLOW);
	printf("%s\\_)(_/ %s(__) ", L_RED, ORANGE);
	printf("%s\\_)__) %s(__) ", YELLOW, GREEN);
	printf("%s(____/ %s\\_)(_/ ", BLUE, VIOLET);
	printf("%s(____) %s\\____/ ", L_RED, ORANGE);
	printf("%s\\____/\n\n", YELLOW);
	printf("%s%s", RESET, BOLD);
	printf("by Natalie Holbrook & Alex Schenk @42 Berlin, August 2024\n\n");
	printf("%s", RESET);
}
