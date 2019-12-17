/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 07:17:49 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 10:15:02 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Find the env_variables in lst, delete and free it from the lst
*/

void	find_and_free_env(t_minishell *minishell, char *name)
{
	t_lstenv_v	*prev;
	t_lstenv_v	*envv;
	t_lstenv_v	*next;

	envv = minishell->env_variables;
	prev = NULL;
	while (envv)
	{
		next = envv->next;
		if (!ft_strcmp(envv->name, name))
		{
			free(envv->name);
			if (envv->value)
				free(envv->value);
			free(envv);
			envv = next;
			if (prev)
				prev->next = envv;
			else
				minishell->env_variables = envv;
			break ;
		}
		prev = envv;
		envv = envv->next;
	}
}

/*
** unset env_variables
*/

int		unset_env(t_minishell *minishell, char **data)
{
	char		*begin;

	begin = *data;
	while (*(*data) && !ft_isspace(*(*data)))
	{
		if (!ft_isalpha(**data) && !ft_isdigit(**data) && **data != '_')
			return (-2);
		(*data)++;
	}
	if (*(*data))
		*(*data)++ = '\0';
	find_and_free_env(minishell, begin);
	return (0);
}

/*
** Run unset command
*/

int		run_unset(t_minishell *minishell)
{
	char	*data;
	int		ret;

	if (!ft_strcmp(minishell->commands->data, ""))
	{
		return (-4); // ERROR NOT ENOUGHT ARGS
	}
	else
	{
		data = minishell->commands->data;
		while (*data)
		{
			ret = unset_env(minishell, &data);
			if (ret == -1)
				return (ret);
			if (ret == -2)
				return (ret); // ERREUR A GERER - INVALID PARAMETER NAME
			if (ft_isspace(*data))
				data++;
		}
	}
	return (0);
}
