/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 21:22:36 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 06:35:13 by lmartin          ###   ########.fr       */
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

int		choice_command(t_minishell *minishell, int type)
{
	int ret;

	if (type == TYPE_CD && (ret = run_cd(minishell)) < 0)
		return (ret);
	else if (type == TYPE_PWD && (ret = run_pwd(minishell)) < 0)
		return (ret);
	else if (type == TYPE_ECHO && (ret = run_echo(minishell)) < 0)
		return (ret);
	else if (type == TYPE_EXPORT && (ret = run_export(minishell)) < 0)
		return (ret);
	else if (type == TYPE_ENV && (ret = run_env(minishell)) < 0)
		return (ret);
	else if (type == TYPE_UNSET && (ret = run_unset(minishell)) < 0)
		return (ret);
	else if (type == TYPE_BIN && (ret = run_bin(minishell)) < 0)
		return (ret);
	return (ret);
}

/*
** Fork a command
*/

int		fork_command(t_minishell *minishell)
{
	int      		ret;
	int				type;
	t_lstcommands	*next;
	t_lstcommands	*prev;

	type = minishell->commands->type;
	next = minishell->commands->next;
	prev = minishell->commands->prev;
	if (type == TYPE_EXIT)
		if (run_exit(minishell) < 0)
			return (-1);
	if ((next && next->type == TYPE_PIPE) || (prev && prev->type == TYPE_PIPE))
	{
		if (!(fork()))
		{
			if (prev && prev->type == TYPE_PIPE)
				dup_and_close_pipe(prev->pipe, 0);
			if (next && next->type == TYPE_PIPE)
				dup_and_close_pipe(next->pipe, 1);
			ret = choice_command(minishell, type);
			if (ret == WRONG_ARG)
				if (write_msg_error(minishell->name, minishell->commands->name,
	"wrong argument") < 0)
					return (-1);
			if (ret == NOT_ENOUGH_ARGS)
				if (write_msg_error(minishell->name, minishell->commands->name,
	"not enough args") < 0)
					return (-1);
			exit(0);
		}
		if (prev && prev->type == TYPE_PIPE)
			close_pipe(prev->pipe);
		while ((wait(NULL)) > 0)
			NULL;
	}
	else
	{
		ret = choice_command(minishell, type);
		if (ret == WRONG_ARG)
			if (write_msg_error(minishell->name, minishell->commands->name,
"wrong argument") < 0)
				return (-1);
		if (ret == NOT_ENOUGH_ARGS)
			if (write_msg_error(minishell->name, minishell->commands->name,
"not enough args") < 0)
				return (-1);
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
		if (next && next->type == TYPE_PIPE)
			if (pipe(next->pipe) < 0)
				return (ERR_PIPE);
		if (fork_command(minishell) < 0)
			return (-1);
		minishell->commands = minishell->commands->next;
	}
	minishell->commands = begin;
	while (minishell->commands)
	{
		next = minishell->commands->next;
		if (minishell->commands->data)
			free(minishell->commands->data);
		free(minishell->commands);
		minishell->commands = next;
	}
	return (0);
}
