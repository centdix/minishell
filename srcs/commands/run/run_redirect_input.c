/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redirect_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 07:07:39 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 09:35:50 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Run <
*/

int		run_redirect_input(t_minishell *minishell)
{
	int		fd;
	char	buffer[2];

	buffer[0] = ' ';
	buffer[1] = '\0';
	if ((fd = open(minishell->commands->data, O_RDONLY)) < 0)
		return (-1);
	while (read(fd, buffer, 1) > 0)
	{
		if ((write(1, buffer, 1)) < 0)
			return (-1);
	}
	close(fd);
	return (0);
}
