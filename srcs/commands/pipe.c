/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 03:42:05 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 04:37:59 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		dup_and_close_pipe(int pipe[2], int dupped)
{
	dup2(pipe[dupped], dupped);
	close(pipe[0]);
	close(pipe[1]);
}

void		close_pipe(int pipe[2])
{
	close(pipe[0]);
	close(pipe[1]);
}
