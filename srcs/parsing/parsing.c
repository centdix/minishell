/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 02:35:38 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 04:42:46 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Choice which command is to parse :
** - command not found or bin
*/

int		choice_parsing4(t_minishell *minishell, char **line)
{
	int		ret;

	if (**line)
	{
		if ((ret = parsing_bin(line, &minishell->commands)) != 0)
			return (ret);
		else
		{
			if ((ret = command_not_found(minishell->name, get_data(line))) < 0)
				return (ret);
			while (*(*line) && !ft_isseparator(*(*line)))
				(*line)++;
			return (ret);
		}
	}
	return (0);
}

/*
** Choice which command is to parse :
** - unset
** - '|' or ';'
*/

int		choice_parsing3(t_minishell *minishell, char **line)
{
	if (!ft_strncmp((*line), "unset", 5) &&
(ft_isspace((*line)[5]) || !(*line)[5]))
	{
		return (parsing_unset(line, &minishell->commands));
	}
	else if (ft_isseparator(*(*line)))
	{
		if (**line == '|')
			return (parsing_pipe(line, &minishell->commands));
		else if (**line == '<')
			return (parsing_redirect_input(line, &minishell->commands));
		else if (!ft_strncmp(*line, ">>", 2))
			return (parsing_redirect_double_output(line, &minishell->commands));
		else if (**line == '>')
			return (parsing_redirect_simple_output(line, &minishell->commands));
		return (1);
	}
	return (0);
}

/*
** Choice which command is to parse :
** - exit
** - export
** - env
*/

int		choice_parsing2(t_minishell *minishell, char **line)
{
	if (!ft_strncmp((*line), "exit", 4) &&
(ft_isspace((*line)[4]) || !(*line)[4]))
	{
		return (parsing_exit(line, &minishell->commands));
	}
	else if (!ft_strncmp((*line), "export", 6) &&
(ft_isspace((*line)[6]) || !(*line)[6]))
	{
		return (parsing_export(line, &minishell->commands));
	}
	else if (!ft_strncmp((*line), "env", 3) &&
(ft_isspace((*line)[3]) || !(*line)[3]))
	{
		return (parsing_env(line, &minishell->commands));
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
		return (parsing_cd(line, &minishell->commands));
	}
	else if (!ft_strncmp((*line), "pwd", 3) &&
(ft_isspace((*line)[3]) || !(*line)[3]))
	{
		return (parsing_pwd(line, &minishell->commands));
	}
	else if (!ft_strncmp((*line), "echo", 4) &&
(ft_isspace((*line)[4]) || !(*line)[4]))
	{
		return (parsing_echo(line, &minishell->commands));
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
		ret = 0;
		while (ft_isspace(*line))
			line++;
		if ((ret = choice_parsing(minishell, &line)) < 0)
			break ;
		if (!ret && (ret = choice_parsing2(minishell, &line)) < 0)
			break ;
		if (!ret && (ret = choice_parsing3(minishell, &line)) < 0)
			break ;
		if (!ret && (ret = choice_parsing4(minishell, &line)) < 0)
			break ;
	}
	if (ret == TOO_MANY_ARGS)
		if (!(write(STDERR_FILENO, "Too many args\n", 14)))
			return (-1);
	return (0);
}
