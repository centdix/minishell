/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 23:08:11 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 05:43:18 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Parse a exit command
*/

int		parsing_exit(char **line, t_lstcommands **commands)
{
	char *begin;
	char *name;

	begin = (*line);
	*line = &(*line)[4];
	if (!(name = get_data_no_space(&begin)))
		return (-1);
	if ((add_back(commands, TYPE_EXIT, name, NULL)) < 0)
		return (-1);
	return (1);
}
