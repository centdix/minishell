/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 21:22:36 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 02:49:02 by lmartin          ###   ########.fr       */
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
		if (!(read(STDIN_FILENO, buffer, 1)))
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
		if (!(read(STDIN_FILENO, buffer, 1)))
			return (NULL);
	}
	return (command);
}

/*
** Choose a command by it's type (minishell->commands->type)
*/

int		choice_command(t_minishell *minishell)
{
	int				type;
	t_lstcommands	*next;
	t_lstcommands	*prev;

	type = minishell->commands->type;
	next = minishell->commands->next;
	prev = minishell->commands->prev;
	if (type == TYPE_EXIT)
	{
		if (run_exit(minishell) < 0)
			return (-1);
	}
	else
	{
		if (!(fork()))
		{
			if (next && next->type == TYPE_PIPE)
			{
				dup2(next->pipe[1], 1);
				close(next->pipe[0]);
				close(next->pipe[1]);
			}
			if (prev && prev->type == TYPE_PIPE)
			{
				dup2(prev->pipe[0], 0);
				close(prev->pipe[1]);
				close(prev->pipe[0]);
			}
			if (type == TYPE_CD && run_cd(minishell) < 0)
				return (-1);
			else if (type == TYPE_PWD && run_pwd(minishell) < 0)
				return (-1);
			else if (type == TYPE_ECHO && run_echo(minishell) < 0)
				return (-1);
			else if (type == TYPE_EXPORT && run_export(minishell) < 0)
				return (-1);
			else if (type == TYPE_ENV && run_env(minishell) < 0)
				return (-1);
			else if (type == TYPE_UNSET && run_unset(minishell) < 0)
				return (-1);
			else if (type == TYPE_BIN && run_bin(minishell) < 0)
				return (-1);
			exit(0);
		}
		while ((wait(NULL)) > 0)
		{
		}
	}
	return (0);
}

/*
** Run every commands that are in lstcommands minishell.commands
*/

int		running_commands(t_minishell *minishell)
{
	t_lstcommands	*begin;
	t_lstcommands	*next;

	begin = minishell->commands;
	while (minishell->commands)
	{
		next = minishell->commands->next;
		printf("TYPE : %d\n", minishell->commands->type);
		printf("DATA : %s$\n", minishell->commands->data);
		if (next && next->type == TYPE_PIPE)
		{
			if (pipe(next->pipe) < 0)
				return (ERR_PIPE);
		}
		if (choice_command(minishell) < 0)
			return (-1);
		minishell->commands = minishell->commands->next;
	}
	minishell->commands = begin;
	while (minishell->commands)
	{
		printf("TYPE : %d\n", minishell->commands->type);
		printf("DATA : %s$\n", minishell->commands->data);
		next = minishell->commands->next;
		if (minishell->commands->data)
			free(minishell->commands->data);
		free(minishell->commands);
		minishell->commands = next;
	}
	return (0);
}
