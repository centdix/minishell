/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 00:30:14 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/11 00:31:39 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Parse a export command
*/

int		parsing_export(char **line, t_lstcommands **commands)
{
	*line = &(*line)[6];
	if ((check_too_many_args(line, 1)) < 0)
		return (TOO_MANY_ARGS);	
	if ((add_back(commands, TYPE_EXPORT, get_data_one_space(line))) < 0)
		return (-1);
	return (1);
}
