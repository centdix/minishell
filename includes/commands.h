/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 21:23:05 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 10:50:03 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# define TYPE_CD 1
# define TYPE_PWD 2
# define TYPE_ECHO 3
# define TYPE_EXIT 4
# define TYPE_EXPORT 5
# define TYPE_ENV 6
# define TYPE_UNSET 7
# define TYPE_BIN 8
# define TYPE_PIPE 9
# define TYPE_RD_DB_OUT 10
# define TYPE_RD_S_OUT 11
# define TYPE_RD_INPUT 12

# include "commands_struct.h"
# include "minishell_struct.h"

/*
** run commands
*/

int					run_bin(t_minishell *minishell);
int					run_cd(t_minishell *minishell);
int					run_echo(t_minishell *minishell);
int					run_env(t_minishell *minishell);
int					run_exit(t_minishell *minishell);
int					run_export(t_minishell *minishell);
int					run_pwd(t_minishell *minishell);
int					run_redirect_double_output(t_minishell *minishell);
int					run_redirect_input(t_minishell *minishell);
int					run_redirect_simple_output(t_minishell *minishell);
int					run_unset(t_minishell *minishell);

/*
** commands
*/

char				*wait_command(char *command);
int					running_commands(t_minishell *minishell);

/*
** lstcommands
*/

void				free_lstcommands(t_lstcommands	**lst);
t_lstcommands		*new_lstcommands(int type, char *name,
char *data, void *prev);
int					add_back(t_lstcommands **lst, int type,
char *name, char *data);

/*
** pipe
*/

void				apply_closing_pipes(t_lstcommands *prev,
t_lstcommands *next, t_minishell *minishell, int type);
void				apply_pipes(t_lstcommands *prev, t_lstcommands *next,
t_minishell *minishell, int type);
void				dup_and_close_pipe(int	pipe[2], int dupped);
void				close_pipe(int	pipe[2]);

#endif
