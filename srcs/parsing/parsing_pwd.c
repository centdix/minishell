/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 08:07:24 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 02:31:28 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Parse a pwd command
*/

int		parsing_pwd(char **line, t_lstcommands **commands)
{
	*line = &(*line)[3];
	if ((check_too_many_args(line, 0)) < 0)
		return (TOO_MANY_ARGS);
	if ((add_back(commands, TYPE_PWD, NULL)) < 0)
		return (-1);
	while (ft_isspace(**line))
		(*line)++;
	return (1);
}
