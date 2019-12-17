/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 21:22:36 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 10:32:33 by lmartin          ###   ########.fr       */
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

	ret = 0;
	if (type == TYPE_CD)
		ret = run_cd(minishell);
	else if (type == TYPE_PWD)
		ret = run_pwd(minishell);
	else if (type == TYPE_ECHO)
		ret = run_echo(minishell);
	else if (type == TYPE_EXPORT)
		ret = run_export(minishell);
	else if (type == TYPE_ENV)
		ret = run_env(minishell);
	else if (type == TYPE_UNSET)
		ret = run_unset(minishell);
	else if (type == TYPE_BIN)
		ret = run_bin(minishell);
	else if (type == TYPE_RD_DB_OUT)
		ret = run_redirect_double_output(minishell);
	else if (type == TYPE_RD_S_OUT)
		ret = run_redirect_simple_output(minishell);
	else if (type == TYPE_RD_INPUT)
		ret = run_redirect_input(minishell);
	return (ret);
}

/*
** Fork a command
*/

int		fork_command(t_lstcommands *prev, t_lstcommands *next,
t_minishell *minishell, int type)
{
	t_lstcommands	*save;
	int				ret;

	if (next && next->type == TYPE_RD_INPUT)
	{
		save = minishell->commands;
		minishell->commands = minishell->commands->next;
		if (fork_command(save, next->next, minishell, next->type) < 0)
			return (-1);
		minishell->commands = save;
	}
	if (!(fork()))
	{
		apply_pipes(prev, next, minishell, type);
		ret = choice_command(minishell, type);
		if (ret < 0 && (command_error(minishell, ret) < 0))
			return (-1);
		exit(0);
	}
	apply_closing_pipes(prev, next, minishell, type);
	while ((wait(NULL)) > 0)
		NULL;
	return (0);
}

/*
** Launch a command
*/

int		launch_command(t_minishell *minishell)
{
	int				ret;
	int				type;
	t_lstcommands	*next;
	t_lstcommands	*prev;

	type = minishell->commands->type;
	next = minishell->commands->next;
	prev = minishell->commands->prev;
	if (type == TYPE_EXIT)
		if (run_exit(minishell) < 0)
			return (-1);
	if ((next && (next->type == TYPE_PIPE || next->type == TYPE_RD_DB_OUT ||
next->type == TYPE_RD_S_OUT || next->type == TYPE_RD_INPUT)) ||
(prev && prev->type == TYPE_PIPE) || (type == TYPE_BIN ||
type == TYPE_RD_DB_OUT || type == TYPE_RD_S_OUT || type == TYPE_RD_INPUT))
	{
		if (fork_command(prev, next, minishell, type) < 0)
			return (-1);
		return (0);
	}
	ret = choice_command(minishell, type);
	if (ret < 0 && (command_error(minishell, ret) < 0))
		return (-1);
	return (0);
}

/*
** Run every commands that are in lstcommands minishell.commands
*/

int		running_commands(t_minishell *minishell)
{
	int				ret;
	t_lstcommands	*begin;
	t_lstcommands	*next;

	ret = 0;
	begin = minishell->commands;
	while (minishell->commands)
	{
		if (minishell->commands->type == TYPE_RD_INPUT)
			minishell->commands = minishell->commands->next;
		if (!minishell->commands)
			break ;
		next = minishell->commands->next;
		if (next && (next->type == TYPE_PIPE || next->type == TYPE_RD_DB_OUT ||
	next->type == TYPE_RD_S_OUT || next->type == TYPE_RD_INPUT))
			if (pipe(next->pipe) < 0)
				return (ERR_PIPE);
		if ((ret = launch_command(minishell)) < 0)
			return (ret);
		minishell->commands = minishell->commands->next;
	}
	minishell->commands = begin;
	free_lstcommands(&minishell->commands);
	g_lastreturn = ret;
	return (ret);
}
