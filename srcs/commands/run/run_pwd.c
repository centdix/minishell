/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 22:20:27 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/13 12:01:36 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Run pwd command
*/

int		run_pwd(t_minishell *minishell)
{
	if (write(1, minishell->path, ft_strlen(minishell->path)) < 0)
		return (ft_setint_and_return(&minishell->last_return, -1));
	if (write(1, "\n", 1) < 0)
		return (ft_setint_and_return(&minishell->last_return, -1));
	return (ft_setint_and_return(&minishell->last_return, 0));
}
