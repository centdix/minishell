/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 23:20:13 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/10 09:23:29 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char *argv[])
{
	t_minishell	minishell;

	header();
	minishell.path = getcwd(minishell.path, 0);
	(void)argc;
	if (!(minishell.name = ft_strjoin(argv[0], ": ")))
		return (-1);
	while (1)
	{
		minishell.commands = NULL;
		if (write_prompt(minishell.path) < 0)
			return(-1);
		if (!(minishell.command_line = ft_strdup("")))
			return (-1);
		if (!(minishell.command_line = wait_command(minishell.command_line)))
			return (-1);
		if (parsing_command(&minishell) < 0)
			return (-1);
		if (running_commands(&minishell) < 0)
			return (-1);
		free(minishell.command_line);
	}
	return (0);
}
