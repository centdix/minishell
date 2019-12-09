/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 23:20:13 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/09 21:08:52 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*wait_command(char *command)
{
	char		buffer[2];
	char		*cpy;

	buffer[1] = '\0';
	if (!(read(0, buffer, 1)))
		return (NULL);
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

int		main(void)
{
	char *command;

	while (1)
	{
		if (!(command = ft_strdup("")))
			return (-1);
		if (!(command = wait_command(command)))
			return (-1);
		printf("command: %s\n", command);
		free(command);
	}
	return (0);
}
