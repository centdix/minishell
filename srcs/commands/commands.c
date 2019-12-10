/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 21:22:36 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/10 22:28:14 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Wait for command to be write in input
*/

char	*wait_command(char *command)
{
	char		buffer[2];
	char		*cpy;

	buffer[0] = ' ';
	buffer[1] = '\0';
	while (buffer[0] != '\n' && ft_isspace(buffer[0]))
	{
		if (!(read(0, buffer, 1)))
			return (NULL);
	}
	while (buffer[0] != '\n')
	{
		if (!(cpy = ft_strdup(command)))
			return (NULL);
		free(command);
		if (!(command = ft_strjoin(cpy, buffer)))
			return (NULL);
		free(cpy);
		if (!(read(0, buffer, 1)))
			return (NULL);
	}
	return (command);
}

/*
** Run every commands that are in lstcommands minishell.commands
*/

int		running_commands(t_minishell *minishell)
{
	t_lstcommands	*next;

	while (minishell->commands)
	{
		if (minishell->commands->type == TYPE_CD)
		{
			if (run_cd(minishell) < 0)
				return (-1);
		}
		else if (minishell->commands->type == TYPE_PWD)
		{
			if (run_pwd(minishell) < 0)
				return (-1);
		}
		else if (minishell->commands->type == TYPE_ECHO)
		{
			if (run_echo(minishell) < 0)
				return (-1);
		}
		next = minishell->commands->next;
		free(minishell->commands->data);
		free(minishell->commands);
		minishell->commands = next;
	}
	return (0);
}
