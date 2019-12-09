/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 21:23:05 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/09 23:39:11 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_H
# define COMMANDS_H

# define CMD_NOT_FOUND "command not found\n"

char	*wait_command(char *command);
int		command_not_found(char *name, char *command);
int		parsing_command(t_minishell *minishell);

#endif
