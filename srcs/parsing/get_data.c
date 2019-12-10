/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 23:03:25 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/10 23:04:07 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Get data (argument), until separator or end
*/

char	*get_data(char **str)
{
	char	*data;
	char	*begin;
	size_t	size;

	while (ft_isspace(**str))
		(*str)++;
	begin = *str;
	size = 0;
	while (!ft_isseparator(*begin) && *begin++)
		size++;
	if (!(data = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	begin = data;
	while (!ft_isseparator(**str) && **str)
		*data++ = *(*str)++;
	*data = '\0';
	return (begin);
}

/*
** Get data (argument), until white space or separator or end
*/

char	*get_data_no_space(char **str)
{
	char	*data;
	char	*begin;
	size_t	size;

	while (ft_isspace(**str))
		(*str)++;
	begin = *str;
	size = 0;
	while (!ft_isspace(*begin) && !ft_isseparator(*begin) && begin++)
		size++;
	if (!(data = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	begin = data;
	while (!ft_isspace(**str) && !ft_isseparator(**str) && **str)
		*data++ = *(*str)++;
	*data = '\0';
	return (begin);
}
