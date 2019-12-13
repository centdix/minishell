/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 23:12:03 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/13 12:13:58 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Run exit command
*/

int		run_exit(t_minishell *minishell)
{
	(void)minishell;
	g_lastreturn = 0;
	exit(0);
}
