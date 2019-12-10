/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 08:08:44 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/11 00:13:13 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Parse a echo command
*/

int		parsing_echo(char **line, t_lstcommands **commands)
{
	*line = &(*line)[4];
	if ((add_back(commands, TYPE_ECHO, get_data_one_space(line))) < 0)
		return (-1);
	return (0);
}
