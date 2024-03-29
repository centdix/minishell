/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 23:20:13 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 15:07:29 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Prompt will print and wait for command
*/

int		prompt(t_minishell *minishell)
{
	int ret;

	while (1)
	{
		minishell->commands = NULL;
		if (write_prompt(minishell->path) < 0)
			return (-1);
		if (!(minishell->command_line = ft_strdup("")))
			return (-1);
		if (!(minishell->command_line = wait_command(minishell->command_line)))
			return (-1);
		if ((ret = parsing_command(minishell)) < 0)
			return (0);
		if (!ret && running_commands(minishell) < 0)
			return (0);
		free(minishell->command_line);
	}
	return (0);
}

/*
** Create a new 'minishell' and launch it
*/

int		launch_minishell(void)
{
	t_minishell minishell;

	minishell.env_variables = g_envv;
	minishell.path = getcwd(NULL, 0);
	parse_bin_path(&minishell);
	g_lastreturn = 0;
	minishell.name = g_name;
	if (prompt(&minishell) < 0)
		return (-1);
	return (0);
}

/*
** Initialize environment variables and the actual path of the shell, then wait
** for prompt
*/

int		main(int argc, char *argv[], char **envv)
{
	pid_t		wpid;
	int			status;

	(void)argc;
	g_lastreturn = 1;
	if (header() < 0)
		return (-1);
	if (!(g_envv = init_env(envv)))
		return (-1);
	g_name = argv[0];
	signal(SIGQUIT, do_nothing);
	if (!(g_pid = fork()))
	{
		if (!launch_minishell())
			return (-1);
		exit(-1);
	}
	else
		signal(SIGINT, signal_handler);
	while ((wpid = wait(&status)) > 0)
		NULL;
	return (0);
}
