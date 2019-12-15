/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 06:25:36 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/15 16:39:59 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define TOO_MANY_ARGS -3
/*
** Errors about command
*/

int		command_not_found(char *name, char *command);
int		check_too_many_args(char **str, int nb_args_max);

#endif
