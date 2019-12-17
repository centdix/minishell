/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 08:53:30 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 10:07:26 by lmartin          ###   ########.fr       */
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
** Get and set exec name in arguments
*/

int		getting_exec_name(char **data, char ***arguments)
{
	char		*ptr;

	if (!ft_strncmp(*data, "/bin/", 5) || !ft_strncmp(*data, "./", 2))
	{
		if (!(*(*arguments)++ = get_data_no_space(data)))
		{
			--(*arguments);
			return (-1);
		}
	}
	else
	{
		if (!(ptr = get_data_no_space(data)))
			return (-1);
		if (!(*(*arguments)++ = ft_strjoin("/bin/", ptr)))
		{
			--(*arguments);
			free(ptr);
			return (-1);
		}
		free(ptr);
	}
	return (0);
}

/*
** Getting args from data and return a allocated array arguments of all data
*/

char	**getting_args(char **data)
{
	size_t		size;
	char		**arguments;
	char		**tmp;

	size = count_args(data);
	if (!(arguments = malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	tmp = arguments;
	if (getting_exec_name(data, &tmp) < 0)
	{
		*tmp = NULL;
		free_2d_array((void **)arguments);
		return (NULL);
	}
	while (--size)
		if (!(*tmp++ = get_data_no_space(data)))
		{
			--tmp;
			*tmp = NULL;
			free_2d_array((void **)arguments);
			return (NULL);
		}
	*tmp = NULL;
	return (arguments);
}

/*
** Run a bin command
*/

int		run_bin(t_minishell *minishell)
{
	char	*data;
	char	**arguments;
	char	**envv;

	data = minishell->commands->data;
	if (!(arguments = getting_args(&data)))
		return (-1);
	if (!(envv = t_lstenv_v_to_array(minishell->env_variables)))
		return (-1);
	execve(arguments[0], arguments, envv);
	//printf("end_bin\n");
	free_2d_array((void **)envv);
	free_2d_array((void **)arguments);
	return (0);
}
