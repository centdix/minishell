/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 23:48:25 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 14:47:36 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string.h>

# include "commands.h"
# include "env_variables.h"
# include "errors.h"
# include "parsing.h"
# include "style.h"
# include "utils.h"

# include "commands_struct.h"
# include "minishell_struct.h"

char		*g_name;
t_lstenv_v	*g_envv;
pid_t		g_pid;
int			g_lastreturn;

int		prompt(t_minishell *minishell);
int		launch_minishell(void);

#endif
