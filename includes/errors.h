/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 06:25:36 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/16 06:29:26 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define TOO_MANY_ARGS -3
# define ERR_PIPE -4

/*
** Errors about command
*/

int		command_not_found(char *name, char *command);
int		check_too_many_args(char **str, int nb_args_max);

#endif
