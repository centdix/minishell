/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 06:25:36 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/17 10:52:01 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define WRONG_ARG -2
# define TOO_MANY_ARGS -3
# define NOT_ENOUGH_ARGS -4
# define ERR_PIPE -5
# define ERR_MALLOC -6
# define ERR_WRITE -7

# define MSG_CMD_NOT_FOUND "command not found"
# define MSG_WRONG_ARGS "wrong argument"
# define MSG_NOT_ENOUGH_ARGS "not enough arguments"
# define MSG_TOO_MANY_ARGS "too many arguments"

/*
** Errors about command
*/

int		command_error(t_minishell *minishell, int ret);
int		write_msg_error(char *prg_name, char *cmd_name, char *msg);
int		command_not_found(char *name, char *command);
int		check_too_many_args(char **str, int nb_args_max);

#endif
