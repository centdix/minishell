/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 22:20:16 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/10 22:27:11 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		run_echo(t_minishell *minishell)
{
	if (write(1, minishell->commands->data, ft_strlen(minishell->commands->data)) < 0)
		return (-1);
	if (write(1, "\n", 1) < 0)
		return (-1);
	return (0);
}
