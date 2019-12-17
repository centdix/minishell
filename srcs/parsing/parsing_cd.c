/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 07:21:44 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 11:30:55 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Parse a cd command
*/

int		parsing_cd(char **line, t_lstcommands **commands)
{
	char	*args;
	char	*begin;
	char	*name;
	char	*data;

	begin = (*line);
	args = &(*line)[2];
	if ((check_too_many_args(&args, 1)) < 0)
		return (TOO_MANY_ARGS);
	*line = &(*line)[2];
	if (!(name = get_data_no_space(&begin)))
		return (-1);
	if (!(data = get_data_one_space(line)))
		return (-1);
	if ((add_back(commands, TYPE_CD, name, data)) < 0)
		return (-1);
	return (1);
}
