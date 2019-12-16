/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 21:22:36 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/16 02:44:51 by lmartin          ###   ########.fr       */
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
	int type;
	int ret;

	type = minishell->commands->type;
	if (type == TYPE_CD && (ret = run_cd(minishell)) < 0)
		return (ret);
	else if (type == TYPE_PWD && (ret = run_pwd(minishell)) < 0)
		return (ret);
	else if (type == TYPE_ECHO && (ret = run_echo(minishell)) < 0)
		return (ret);
	else if (type == TYPE_EXIT && (ret = run_exit(minishell)) < 0)
		return (ret);
	else if (type == TYPE_EXPORT && (ret = run_export(minishell)) < 0)
		return (ret);
	else if (type == TYPE_ENV && (ret = run_env(minishell)) < 0)
		return (ret);
	else if (type == TYPE_UNSET && (ret = run_unset(minishell)) < 0)
		return (ret);
	else if (type == TYPE_BIN && (ret = run_bin(minishell)) < 0)
		return (ret);
	return (0);
}

/*
** Run every commands that are in lstcommands minishell.commands
*/

int		running_commands(t_minishell *minishell)
{
	t_lstcommands	*next;
	int 			ret;

	while (minishell->commands)
	{
		ret = choice_command(minishell);
		if (ret == WRONG_ARG)
			write(STDERR_FILENO, "wrong argument\n", 15);
		if (ret == NOT_ENOUGH_ARGS)
			write(STDERR_FILENO, "not enough args\n", 16);
		next = minishell->commands->next;
		free(minishell->commands->data);
		free(minishell->commands);
		minishell->commands = next;
	}
	return (0);
}
