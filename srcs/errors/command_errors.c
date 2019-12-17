/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 06:24:23 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 11:29:35 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Command error lead to write error
*/

int		command_error(char *name, char *cmd_name, int ret)
{
	if (ret == WRONG_ARG)
		if (write_msg_error(name, cmd_name, MSG_WRONG_ARGS) < 0)
			return (ERR_WRITE);
	if (ret == NOT_ENOUGH_ARGS)
		if (write_msg_error(name, cmd_name, MSG_NOT_ENOUGH_ARGS) < 0)
			return (ERR_WRITE);
	if (ret == TOO_MANY_ARGS)
		if (write_msg_error(name, cmd_name, MSG_TOO_MANY_ARGS) < 0)
			return (ERR_WRITE);
	if (ret == CMD_NOT_FOUND)
		if (write_msg_error(name, cmd_name, MSG_CMD_NOT_FOUND) < 0)
			return (ERR_WRITE);
	return (0);
}

/*
** Write a message error
*/

int		write_msg_error(char *prg_name, char *cmd_name, char *msg)
{
	if (write(STDERR_FILENO, prg_name, ft_strlen(prg_name)) < 0)
		return (ERR_WRITE);
	if (write(STDERR_FILENO, ": ", 2) < 0)
		return (ERR_WRITE);
	if (write(STDERR_FILENO, cmd_name, ft_strlen(cmd_name)) < 0)
		return (ERR_WRITE);
	if (write(STDERR_FILENO, ": ", 2) < 0)
		return (ERR_WRITE);
	if (write(STDERR_FILENO, msg, ft_strlen(msg)) < 0)
		return (ERR_WRITE);
	if (write(STDERR_FILENO, "\n", 1) < 0)
		return (ERR_WRITE);
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
