/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 23:20:13 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/10 22:42:13 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		prompt(t_minishell *minishell)
{
	minishell->commands = NULL;
	if (write_prompt(minishell->path) < 0)
		return (-1);
	if (!(minishell->command_line = ft_strdup("")))
		return (-1);
	if (!(minishell->command_line = wait_command(minishell->command_line)))
		return (-1);
	if (parsing_command(minishell) < 0)
		return (-1);
	if (running_commands(minishell) < 0)
		return (-1);
	free(minishell->command_line);
	return (0);
}

/*
** Initialize environment variables and the actual path of the shell, then wait
** for prompt
*/

int		main(int argc, char *argv[], char **envv)
{
	t_minishell	minishell;

	if (!(minishell.env_variables = init_env(envv)))
		return (-1);
	if (header() < 0)
		return (-1);
	minishell.path = getcwd(minishell.path, 0);
	(void)argc;
	if (!(minishell.name = ft_strjoin(argv[0], ": ")))
		return (-1);
	while (1)
	{
		if (prompt(&minishell) < 0)
			return (-1);
	}
	return (0);
}
