/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 07:21:44 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/10 09:30:10 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		parsing_cd(char **line, t_lstcommands **commands)
{
	*line = &(*line)[2];
	if ((add_back(commands, TYPE_CD, get_data_no_space(line))) < 0)
		return (-1);
	return (0);
}
