/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 06:24:23 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/10 06:48:17 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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
	if ((write(1, command_line, ft_strlen(command_line))) < 0)
		return (-2);
	free(command_line);
	if ((write(1, "\n", 1)) < 0)
		return (-2);
	return (0);
}

/*
** Check if they are more arguments to a command
*/

int		check_too_many_args(char **str)
{
	while (**str && !ft_isseparator(**str) && !ft_isspace(**str))
		str++;
	if (**str && !(ft_isseparator(**str)))
		return (-1);
	return (0);
}
