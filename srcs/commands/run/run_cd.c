/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 22:19:12 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/10 22:24:40 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		run_cd(t_minishell *minishell)
{
	if (!ft_strcmp(minishell->commands->data, ""))
	{
		minishell->commands->data = ft_strdup(get_env_value(minishell->env_variables, "HOME"));
	}
	if (chdir(minishell->commands->data) > 0)
		return (-1);
	free(minishell->path);
	minishell->path = NULL;
	minishell->path = getcwd(minishell->path, 0);
	return (0);
}
