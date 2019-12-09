/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 21:22:36 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/09 23:41:10 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int		command_not_found(char *name, char *command)
{
	char *command_line;
	char *cpy;

	if (!(cpy = ft_strjoin(name, command)))
		return (-1);
	if (!(command_line = ft_strjoin(cpy, ": ")))
		return (-1);
	free(cpy);
	if (!(cpy = ft_strdup(command_line)))
		return (-1);
	free(command_line);
	if (!(command_line = ft_strjoin(cpy, CMD_NOT_FOUND)))
		return (-1);
	if ((write(1, command_line, ft_strlen(command_line))) < 0)
		return (-2);
	free(command_line);
	return (0);
}

int		parsing_command(t_minishell *minishell)
{
	char *command;
	int ret;

	command = minishell->command;
	if (!(ft_strcmp(command, "")))
		return (0);
	if ((ret = command_not_found(minishell->name, command)) < 0)
		return (ret);
	return (0);
}
