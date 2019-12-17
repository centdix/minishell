/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 02:52:19 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 05:38:32 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parsing_pipe(char **line, t_lstcommands **commands)
{
	char *begin;
	char *name;

	begin = (*line);
	(*line)++;
	if (!(name = get_data_no_space(&begin)))
		return (-1);
	if ((add_back(commands, TYPE_PIPE, name, NULL) < 0))
		return (-1);
	while (ft_isspace(**line))
		(*line)++;
	return (1);
}
