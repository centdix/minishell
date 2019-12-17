/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 07:12:01 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 04:43:14 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Parse a unset command
*/

int		parsing_unset(char **line, t_lstcommands **commands)
{
	*line = &(*line)[5];
	if ((check_too_many_args(line, 1)) < 0)
		return (TOO_MANY_ARGS);
	if ((add_back(commands, TYPE_UNSET, get_data_one_space(line))) < 0)
		return (-1);
	return (1);
}
