/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 07:12:01 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 05:43:33 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Parse a unset command
*/

int		parsing_unset(char **line, t_lstcommands **commands)
{
	char *begin;
	char *name;
	char *data;

	begin = (*line);
	*line = &(*line)[5];
	if (!(name = get_data_no_space(&begin)))
		return (-1);
	if (!(data = get_data_one_space(line)))
		return (-1);
	if ((add_back(commands, TYPE_UNSET, name, data)) < 0)
		return (-1);
	return (1);
}
