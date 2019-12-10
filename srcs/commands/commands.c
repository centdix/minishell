/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 21:22:36 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/10 06:04:28 by lmartin          ###   ########.fr       */
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

int		running_commands(t_minishell *minishell)
{
	t_lstcommands	*next;

	while (minishell->commands)
	{
		if (minishell->commands->type == TYPE_CD)
		{
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
		next = minishell->commands->next;
		free(minishell->commands->data);
		free(minishell->commands);
		minishell->commands = next;
	}
	return (0);
}

int		command_not_found(char *name, char *command)
{
	char	*begin;
	char	*command_line;
	char	*cpy;
	size_t	i;

	i = 0;
	begin = ft_strdup(command);
	while (command[i] && !ft_isspace(command[i]) && !ft_isseparator(command[i]))
		i++;
	begin[i] = '\0';
	if (!(command_line = ft_strjoin(name, CMD_NOT_FOUND)))
		return (-1);
	if (!(cpy = ft_strjoin(command_line, ": ")))
		return (-1);
	free(command_line);
	if (!(command_line = ft_strjoin(cpy, begin)))
		return (-1);
	free(begin);
	free(cpy);
	if ((write(1, command_line, ft_strlen(command_line))) < 0)
		return (-2);
	free(command_line);
	if ((write(1, "\n", 1)) < 0)
		return (-2);
	return (0);
}
