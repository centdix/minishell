/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 08:08:44 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/10 08:10:01 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parsing_echo(char **line, t_lstcommands **commands)
{
	*line = &(*line)[4];
	if ((add_back(commands, TYPE_ECHO, get_data(line))) < 0) // A CHANGER
		return (-1);
	return (0);
}
