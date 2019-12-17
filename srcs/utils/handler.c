/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 14:46:18 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 21:40:35 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Handle SIGQUIT (CTRL \) Do nothing.
*/

void	do_nothing(int nb)
{
	(void)nb;
	if (write(STDOUT_FILENO, " \b\b \b", 5) < 0)
		return ;
	return ;
}

/*
** Handle SIGINT (CTRL + C)
*/

void	signal_handler(int nb)
{
	(void)nb;
	if (write(STDOUT_FILENO, "\b\b  \n", 5) < 0)
		return ;
	if (kill(g_pid, SIGTERM) < 0)
		exit(-1);
	if (!(g_pid = fork()))
	{
		if ((launch_minishell()) < 0)
			return ;
		exit(-1);
	}
	else
		signal(SIGINT, signal_handler);
}
