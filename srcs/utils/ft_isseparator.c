/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isseparator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 04:59:39 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/16 02:50:34 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Check if char c is a separator of command line
*/

int		ft_isseparator(char c)
{
	return ((c == ';' || c == '|' || c == '<' || c == '>'));
}
