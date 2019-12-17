/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 00:30:14 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 05:43:07 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Parse a export command
*/

int		parsing_export(char **line, t_lstcommands **commands)
{
	char *begin;
	char *name;
	char *data;

	begin = (*line);
	*line = &(*line)[6];
	if (!(name = get_data_no_space(&begin)))
		return (-1);
	if (!(data = get_data_one_space(line)))
		return (-1);
	if (add_back(commands, TYPE_EXPORT, name, data) < 0)
		return (-1);
	return (1);
}
