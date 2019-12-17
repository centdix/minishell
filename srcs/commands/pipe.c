/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 03:42:05 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 09:55:15 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Close or not pipe depend on fork_command
*/

void		apply_closing_pipes(t_lstcommands *prev, t_lstcommands *next,
t_minishell *minishell, int type)
{
	if ((prev && prev->type == TYPE_PIPE))
		close_pipe(prev->pipe);
	if (next && next->type == TYPE_RD_INPUT)
		close_pipe(next->pipe);
	if ((type == TYPE_RD_DB_OUT || type == TYPE_RD_S_OUT))
		close_pipe(minishell->commands->pipe);
}

/*
** Apply pipes for fork_command
*/

void		apply_pipes(t_lstcommands *prev, t_lstcommands *next,
t_minishell *minishell, int type)
{
	if ((prev && prev->type == TYPE_PIPE))
		dup_and_close_pipe(prev->pipe, 0);
	if ((next && next->type == TYPE_RD_INPUT))
		dup_and_close_pipe(next->pipe, 0);
	if ((type == TYPE_RD_DB_OUT || type == TYPE_RD_S_OUT))
		dup_and_close_pipe(minishell->commands->pipe, 0);
	if (type == TYPE_RD_INPUT)
		dup_and_close_pipe(minishell->commands->pipe, 1);
	if (next && (next->type == TYPE_PIPE || next->type == TYPE_RD_DB_OUT ||
next->type == TYPE_RD_S_OUT))
		dup_and_close_pipe(next->pipe, 1);
}

/*
** Dup on the dupped side a pipe and close it
*/

void		dup_and_close_pipe(int pipe[2], int dupped)
{
	dup2(pipe[dupped], dupped);
	close(pipe[0]);
	close(pipe[1]);
}

/*
** Close a pipe
*/

void		close_pipe(int pipe[2])
{
	close(pipe[0]);
	close(pipe[1]);
}
