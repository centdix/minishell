/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 08:53:30 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/12 02:28:35 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


size_t	count_args(char *data)
{
	size_t	size;

	size = 0;
	while (*data)
	{
		if (ft_isspace(*data))
		{
			while (ft_isspace(*data))
				data++;
		}
		else
		{
			size++;
			while (*data && !ft_isspace(*data))
				data++;
		}
	}
	return (size);
}

char	**getting_args(char **data)
{
	char 	*ptr;
	size_t	size;
	char 	**arguments;
	char 	**tmp;

	while (ft_isspace(**data))
		(*data)++;
	size = count_args(*data);
	if (!(arguments = malloc(sizeof(char *) * (size))))
		return (NULL);
	tmp = arguments;
	if (ft_strncmp(*data, "/bin/", 5))
	{
		ptr = get_data_no_space(data);
		*tmp = ft_strjoin("/bin/", ptr);
		free(ptr);
	}
	else
		*tmp = get_data_no_space(data);
	tmp++;
	while (--size)
	{
		if (!(*tmp = get_data_no_space(data)))
			return (NULL);
		tmp++;
	}
	*tmp = NULL;
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
