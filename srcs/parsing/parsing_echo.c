/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 08:08:44 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/13 09:12:50 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Parse a echo command
*/

int		parsing_echo(char **line, t_lstcommands **commands)
{
	char *data;

	*line = &(*line)[4];
	if (!(data = get_data(line)))
		return (-1);
	if ((add_back(commands, TYPE_ECHO, data) < 0))
		return (-1);
	return (0);
}
