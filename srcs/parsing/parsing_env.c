/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 02:24:02 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 05:41:39 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Parse a env command
*/

int		parsing_env(char **line, t_lstcommands **commands)
{
	char *begin;
	char *name;
	char *data;

	*line = &(*line)[3];
	begin = (*line);
	if (!(name = get_data_no_space(&begin)))
		return (-1);
	if (!(data = get_data_one_space(line)))
		return (-1);
	if (add_back(commands, TYPE_ENV, name, data) < 0)
		return (-1);
	return (1);
}
