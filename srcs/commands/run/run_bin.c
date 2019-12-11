/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 08:53:30 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/11 10:10:44 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Run a bin command
*/

int		run_bin(t_minishell *minishell)
{
	int	ret;
	char *path;
	char *exec;
	char *data;
	char **arguments;
	char **envv;
	pid_t pid;

	data = minishell->commands->data;
	if (ft_strncmp(data, "/bin/", 5))
	{
		exec = get_data_no_space(&data);
		path = ft_strjoin("/bin/", exec);
		free(exec);
	}
	if (!(arguments = malloc(sizeof(char *) * 3)))
		return (-1);
	while (ft_isspace(*data))
		data++;
	if (!ft_strcmp(data, ""))
	{
		if (!(data = malloc(sizeof(char) * 2)))
			return (-1);
		data[0] = '.';
		data[1] = '\0';
	}
	arguments[0] = path;
	arguments[1] = data;
	arguments[2] = NULL;
	if (!(pid = fork()))
	{
		envv = t_lstenv_v_to_array(minishell->env_variables);
		ret = execve(arguments[0], arguments, envv);
		while (*envv)
			free((*envv)++);
		free(*envv);
		free(envv);
		exit(0);
	}
	else
		wait(NULL);
	return (0);
}
