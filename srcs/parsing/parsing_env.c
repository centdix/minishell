/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 02:24:02 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/15 16:26:59 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Parse a env command
*/

int		parsing_env(char **line, t_lstcommands **commands)
{
	*line = &(*line)[3];
	if ((add_back(commands, TYPE_ENV, get_data_one_space(line))) < 0)
		return (-1);
	return (0);
}
