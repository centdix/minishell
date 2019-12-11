/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 02:35:38 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/11 02:29:51 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Choice which command is to parse :
** - exit
** - export
** - '|' or ';'
** - command not found
*/

int		choice_parsing2(t_minishell *minishell, char **line)
{
	int		ret;

	if (!ft_strncmp((*line), "exit", 4) &&
(ft_isspace((*line)[4]) || !(*line)[4]))
	{
		if (parsing_exit(line, &minishell->commands) < 0)
			return (-1);
		return (1);
	}
	else if (!ft_strncmp((*line), "export", 6) &&
(ft_isspace((*line)[6]) || !(*line)[6]))
	{
		if (parsing_export(line, &minishell->commands) < 0)
			return (-1);
		return (1);
	}
	else if (!ft_strncmp((*line), "env", 3) &&
(ft_isspace((*line)[3]) || !(*line)[3]))
	{
		if (parsing_env(line, &minishell->commands) < 0)
			return (-1);
		return (1);
	}
	else if (ft_isseparator(*(*line)))
		(*line)++; // A CHANGER
	else if (**line)
	{
		if ((ret = command_not_found(minishell->name, get_data(line))) < 0)
			return (ret);
		while (*(*line) && !ft_isseparator(*(*line)))
			(*line)++;
	}
	return (0);
}

/*
** Choice which command is to parse :
** - cd
** - pwd
** - echo
*/

int		choice_parsing(t_minishell *minishell, char **line)
{
	if (!ft_strncmp((*line), "cd", 2) &&
(ft_isspace((*line)[2]) || !(*line)[2]))
	{
		if (parsing_cd(line, &minishell->commands) < 0)
			return (-1);
		return (1);
	}
	else if (!ft_strncmp((*line), "pwd", 3) &&
(ft_isspace((*line)[3]) || !(*line)[3]))
	{
		if (parsing_pwd(line, &minishell->commands) < 0)
			return (-1);
		return (1);
	}
	else if (!ft_strncmp((*line), "echo", 4) &&
(ft_isspace((*line)[4]) || !(*line)[4]))
	{
		if (parsing_echo(line, &minishell->commands) < 0)
			return (-1);
		return (1);
	}
	return (0);
}

/*
** Parse the command line and get command then add them to lstcommands
** minishell->commands
*/

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
		if ((ret = choice_parsing(minishell, &line)) < 0)
			return (-1);
		if (!ret && choice_parsing2(minishell, &line) < 0)
			return (-1);
	}
	return (0);
}
