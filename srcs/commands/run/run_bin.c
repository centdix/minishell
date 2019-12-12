/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 08:53:30 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/12 03:21:10 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Count the number of args in data
*/

size_t	count_args(char **data)
{
	char		*ptr;
	size_t		size;

	while (ft_isspace(**data))
		(*data)++;
	size = 0;
	ptr = *data;
	while (*ptr)
	{
		if (ft_isspace(*ptr))
		{
			while (ft_isspace(*ptr))
				ptr++;
		}
		else
		{
			size++;
			while (*ptr && !ft_isspace(*ptr))
				ptr++;
		}
	}
	return (size);
}

/*
** Getting args from data and return a allocated array arguments of all data
*/

char	**getting_args(char **data)
{
	size_t		size;
	char		*ptr;
	char		**arguments;
	char		**tmp;

	size = count_args(data);
	if (!(arguments = malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	tmp = arguments;
	if (ft_strncmp(*data, "/bin/", 5))
	{
		if (!(ptr = get_data_no_space(data)))
			return (NULL);
		if (!(*tmp++ = ft_strjoin("/bin/", ptr)))
			return (NULL);
		free(ptr);
	}
	else if (!(*tmp++ = get_data_no_space(data)))
		return (NULL);
	while (--size)
		if (!(*tmp++ = get_data_no_space(data)))
			return (NULL); // FAIRE UN TRUC POUR LE NO LEAKS
	*tmp = NULL;
	return (arguments);
}

/*
** Free 2D array
*/

void	free_2d_array(void **array)
{
	void **ptr;

	ptr = array;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(array);
}

/*
** Run a bin command
*/

int		run_bin(t_minishell *minishell)
{
	char	*data;
	char	**arguments;
	char	**envv;
	pid_t	pid;

	data = minishell->commands->data;
	if (!(arguments = getting_args(&data)))
		return (-1);
	if (!(envv = t_lstenv_v_to_array(minishell->env_variables)))
		return (-1);
	if (!(pid = fork()))
	{
		if (execve(arguments[0], arguments, envv) < 0)
			return (-2);
		exit(0);
	}
	else
		wait(NULL);
	free_2d_array((void **)envv);
	free_2d_array((void **)arguments);
	return (0);
}
