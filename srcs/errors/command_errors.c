/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 06:24:23 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 06:02:15 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Write a message error
*/

int		write_msg_error(char *prg_name, char *cmd_name, char *msg)
{
	if (write(STDERR_FILENO, prg_name, ft_strlen(prg_name)) < 0)
		return (-1);
	if (write(STDERR_FILENO, cmd_name, ft_strlen(cmd_name)) < 0)
		return (-1);
	if (write(STDERR_FILENO, ": ", 2) < 0)
		return (-1);
	if (write(STDERR_FILENO, msg, ft_strlen(msg)) < 0)
		return (-1);
	if (write(STDERR_FILENO, "\n", 1) < 0)
		return (-1);
	return (0);
}

/*
** If a command isn't find, print : 'program name: not found: command'
*/

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
	if ((write(STDERR_FILENO, command_line, ft_strlen(command_line))) < 0)
		return (-2);
	free(command_line);
	if ((write(STDERR_FILENO, "\n", 1)) < 0)
		return (-2);
	return (0);
}

/*
** Check if they are more arguments to a command
*/

int		check_too_many_args(char **str, int nb_args_max)
{
	char	*ptr;
	int		was_args;

	ptr = *str;
	was_args = 0;
	while (*ptr && !ft_isseparator(*ptr))
	{
		if (ft_isspace(*ptr))
		{
			was_args = 0;
			while (ft_isspace(*ptr))
				(ptr)++;
		}
		else
		{
			if (!was_args)
				was_args = 1 + (0 * nb_args_max--);
			(ptr)++;
		}
	}
	if (nb_args_max < 0)
		return (-1);
	return (0);
}
