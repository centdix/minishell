/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 02:35:38 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/10 06:03:45 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_too_many_args(char **str)
{
	while (**str && !ft_isseparator(**str) && !ft_isspace(**str))
		str++;
	if (**str && !(ft_isseparator(**str)))
		return (-1);
	return (0);
}

char	*get_data(char **str)
{
	char	*data;
	char	*begin;
	size_t	size;

	while (ft_isspace(**str))
		(*str)++;
	begin = *str;
	size = 0;
	while (!ft_isspace(*begin) && !ft_isseparator(*begin) && begin++)
		size++;
	if (!(data = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	begin = data;
	while (!ft_isspace(**str) && !ft_isseparator(**str) && **str)
		*data++ = *(*str)++;
	*data = '\0';
	return (begin);
}

int		parsing_command(t_minishell *minishell)
{
	char			*line;
	int				ret;

	line = minishell->command_line;
	if (!(ft_strcmp(line, "")))
		return (0);
	while (*line)
	{
		while (ft_isspace(*line))
			line++;
		if (line[0] == 'c' && line[1] == 'd' && (ft_isspace(line[2]) || !line[2]))
		{
			line = &line[2];
			if ((add_back(&minishell->commands, TYPE_CD, get_data(&line))) < 0)
				return (-1);
		}
		else if (line[0] == 'p' && line[1] == 'w' && line[2] == 'd' &&
(ft_isspace(line[3]) || !line[3]))
		{
			line = &line[3];
			if ((check_too_many_args(&line)) < 0)
				return (-3);
			if ((add_back(&minishell->commands, TYPE_PWD, NULL)) < 0)
				return (-1);
		}
		else if (ft_isseparator(*line))
		{
			line++;
		}
		else
		{
			if ((ret = command_not_found(minishell->name, line)) < 0)
				return (ret);
			while (*line && !ft_isspace(*line) && !ft_isseparator(*line))
				line++;
		}
	}
	return (0);
}
