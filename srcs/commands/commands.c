/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 21:22:36 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/11 09:40:12 by lmartin          ###   ########.fr       */
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
** Choose a command by it's type (minishell->commands->type)
*/

int		choice_command(t_minishell *minishell)
{
	int type;

	type = minishell->commands->type;
	if (type == TYPE_CD && run_cd(minishell) < 0)
		return (-1);
	else if (type == TYPE_PWD && run_pwd(minishell) < 0)
		return (-1);
	else if (type == TYPE_ECHO && run_echo(minishell) < 0)
		return (-1);
	else if (type == TYPE_EXIT && run_exit(minishell) < 0)
		return (-1);
	else if (type == TYPE_EXPORT && run_export(minishell) < 0)
		return (-1);
	else if (type == TYPE_ENV && run_env(minishell) < 0)
		return (-1);
	else if (type == TYPE_UNSET && run_unset(minishell) < 0)
		return (-1);
	else if (type == TYPE_BIN && run_bin(minishell) < 0)
		return (-1);
	return (0);
}

/*
** Run every commands that are in lstcommands minishell.commands
*/

int		running_commands(t_minishell *minishell)
{
	t_lstcommands	*next;

	while (minishell->commands)
	{
		if (choice_command(minishell) < 0)
			return (-1);
		next = minishell->commands->next;
		free(minishell->commands->data);
		free(minishell->commands);
		minishell->commands = next;
	}
	return (0);
}
