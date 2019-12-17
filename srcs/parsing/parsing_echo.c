/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 08:08:44 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 05:36:53 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Parse a echo command
*/

int		parsing_echo(char **line, t_lstcommands **commands)
{
	char *begin;
	char *name;
	char *data;

	begin = (*line);
	*line = &(*line)[4];
	if (!(data = get_data(line)))
		return (-1);
	if (!(name = get_data_no_space(&begin)))
		return (-1);
	if ((add_back(commands, TYPE_ECHO, name, data) < 0))
		return (-1);
	return (1);
}
