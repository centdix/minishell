/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 23:08:11 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/10 23:11:04 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Parse a exit command
*/

int		parsing_exit(char **line, t_lstcommands **commands)
{
	*line = &(*line)[4];
	if ((add_back(commands, TYPE_EXIT, NULL)) < 0)
		return (-1);
	return (0);
}
