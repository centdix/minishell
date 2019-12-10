/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 21:22:36 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/10 10:24:54 by lmartin          ###   ########.fr       */
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
			if (!ft_strcmp(minishell->commands->data, ""))
			{
				minishell->commands->data = ft_strdup(get_env_value(minishell->env_variables, "HOME"));
			}
			if (chdir(minishell->commands->data) > 0)
				return (-1);
			free(minishell->path);
			minishell->path = NULL;
			minishell->path = getcwd(minishell->path, 0);
		}
		else if (minishell->commands->type == TYPE_PWD)
		{
			write(1, minishell->path, ft_strlen(minishell->path));
			write(1, "\n", 1);
		}
		else if (minishell->commands->type == TYPE_ECHO)
		{
			write(1, minishell->commands->data, ft_strlen(minishell->commands->data));
			write(1, "\n", 1);
		}
		next = minishell->commands->next;
		free(minishell->commands->data);
		free(minishell->commands);
		minishell->commands = next;
	}
	return (0);
}
