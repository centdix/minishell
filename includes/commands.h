/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 21:23:05 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/10 23:13:20 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# define CMD_NOT_FOUND "command not found"

# define TYPE_PIPE 0
# define TYPE_CD 1
# define TYPE_PWD 2
# define TYPE_ECHO 3
# define TYPE_EXIT 4

# include "commands_struct.h"
# include "minishell_struct.h"

/*
** run commands
*/

int					run_cd(t_minishell *minishell);
int					run_echo(t_minishell *minishell);
int					run_exit(t_minishell *minishell);
int					run_pwd(t_minishell *minishell);

/*
** commands
*/

char				*wait_command(char *command);
int					running_commands(t_minishell *minishell);

/*
** lstcommands
*/

t_lstcommands		*new_lstcommands(int type, char *data);
int					add_back(t_lstcommands **lst, int type, char *data);

#endif
