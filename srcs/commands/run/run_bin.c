/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 08:53:30 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/12 01:06:57 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_options(char **data)
{
	char saved_char;
	char *tmp;
	char *end;
	char *options;

	tmp = *data;
	end = *data;
	if (**data == '-')
	{
		while (**data)
		{
			if (ft_isspace(**data))
			{
				while (ft_isspace(**data))
					(*data)++;
				if (**data != '-')
					break;
			}
			if (**data && !ft_isspace(**data))
				end = ++(*data);
		}
	}
	saved_char = *end;
	*end = '\0';
	if (!(options = ft_strdup(tmp)))
		return (NULL);
	*end = saved_char;
	return (options);
}

char	*get_bin(char **data)
{
	char *tmp;
	char *bin;

	if (ft_strncmp(*data, "/bin/", 5))
	{
		if (!(tmp = get_data_no_space(data)))
			return (NULL);
		if (!(bin = ft_strjoin("/bin/", tmp)))
		{
			free(tmp);
			return (NULL);
		}
	}
	else
	{
		if (!(bin = get_data_no_space(data)))
			return (NULL);
	}
	return (bin);
}

char	**getting_args(char **data)
{
	char **arguments;

	if (!(arguments = malloc(sizeof(char *) * 3)))
		return (NULL);
	if (!(arguments[0] = get_bin(data)))
	{
		free(arguments);
		return (NULL);
	}
	if (ft_strcmp(*data, ""))
	{
		if (!(arguments[1] = get_options(data)))
		{
			free(arguments[0]);
			free(arguments);
			return (NULL);
		}
	}
	else
	{
		arguments[1] = NULL;
	}
	if (ft_strcmp(*data, ""))
	{
		if (!(arguments[2] = get_data_one_space(data)))
		{
			free(arguments[0]);
			free(arguments[1]);
			free(arguments);
			return (NULL);
		}
	}
	else
	{
		if (!(arguments[2] = ft_strdup(".")))
		{
			free(arguments[0]);
			free(arguments[1]);
			free(arguments);
			return (NULL);
		}
	}
	return (arguments);
}

/*
** Run a bin command
*/

int		run_bin(t_minishell *minishell)
{
	int	ret;
	char *data;
	char **arguments;
	char **envv;
	pid_t pid;

	data = minishell->commands->data;
	if (!(arguments = getting_args(&data)))
		return (-1);
	printf("%s - %s - %s\n", arguments[0], arguments[1], arguments[2]);
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
