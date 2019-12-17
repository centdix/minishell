/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redirect_double_output.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 07:07:01 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 09:03:41 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Read from stdin and fill to_write
*/

int		read_and_fill_double_output(char **to_write)
{
	char	*cpy;
	int		count;
	char	buffer[2];

	buffer[0] = ' ';
	buffer[1] = '\0';
	count = 0;
	while (read(0, buffer, 1) > 0)
	{
		if (!(cpy = ft_strdup(*to_write)))
			return (-1);
		free(*to_write);
		if (!(*to_write = ft_strjoin(cpy, buffer)))
			return (-1);
		free(cpy);
		count++;
	}
	return (count);
}

/*
** Run >>
*/

int		run_redirect_double_output(t_minishell *minishell)
{
	int		fd;
	int		count;
	char	*to_write;

	if ((fd = open(minishell->commands->data,
O_WRONLY | O_CREAT | O_APPEND, 0644)) < 0)
		return (-1);
	if (!(to_write = ft_strdup("")))
		return (-1);
	if ((count = read_and_fill_double_output(&to_write)) < 0)
		return (-1);
	if ((write(fd, to_write, count)) < 0)
		return (-1);
	close(fd);
	return (0);
}
