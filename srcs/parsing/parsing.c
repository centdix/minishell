/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 02:35:38 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/10 07:11:44 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Get data (argument), until separator or end
*/

char	*get_data(char **str)
{
	char	*data;
	char	*begin;
	size_t	size;

	while (ft_isspace(**str))
		(*str)++;
	begin = *str;
	size = 0;
	while (!ft_isseparator(*begin) && *begin++)
		size++;
	if (!(data = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	begin = data;
	while (!ft_isseparator(**str) && **str)
		*data++ = *(*str)++;
	*data = '\0';
	return (begin);
}

/*
** Get data (argument), until white space or separator or end
*/

char	*get_data_no_space(char **str)
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
		if (!ft_strncmp(line, "cd", 2) && (ft_isspace(line[2]) || !line[2]))
		{
			line = &line[2];
			if ((add_back(&minishell->commands, TYPE_CD, get_data_no_space(&line))) < 0)
				return (-1);
		}
		else if (!ft_strncmp(line, "pwd", 3) && (ft_isspace(line[3]) || !line[3]))
		{
			line = &line[3];
			if ((check_too_many_args(&line)) < 0)
				return (-3);
			if ((add_back(&minishell->commands, TYPE_PWD, NULL)) < 0)
				return (-1);
		}
		else if (!ft_strncmp(line, "echo", 4) && (ft_isspace(line[4]) || !line[4]))
		{
			line = &line[4];
			if ((add_back(&minishell->commands, TYPE_ECHO, get_data(&line))) < 0) // A CHANGER
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
