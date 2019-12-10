/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 23:03:25 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/11 00:12:29 by lmartin          ###   ########.fr       */
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

/*
** Fill data for data_one_space
*/

void	fill_data_one_space(char **str, char **data)
{
	int		b;
	char	saved_quote;

	b = 0;
	saved_quote = 0;
	while (!ft_isseparator(**str) && **str)
	{
		if (saved_quote && !(b *= 0) && **str == saved_quote)
			saved_quote = 0;
		else if (saved_quote)
			*(*data)++ = *(*str);
		else
		{
			saved_quote = (ft_isquote(**str)) ? **str : 0;
			if (!saved_quote)
			{
				if (!b || !ft_isspace(**str))
					*(*data)++ = *(*str);
				b = (ft_isspace(**str)) ? 1 : 0;
			}
		}
		(*str)++;
	}
	*(*data) = '\0';
}

/*
** Get size to malloc for data_one_space
*/

size_t	get_size_one_space(char **str)
{
	int		b;
	char	*begin;
	size_t	size;
	char	saved_quote;

	begin = *str;
	size = 0;
	b = 0;
	saved_quote = 0;
	while (!ft_isseparator(*begin) && *begin)
	{
		if (saved_quote && (b *= 0) && *begin == saved_quote)
			saved_quote = 0;
		else if (saved_quote)
			size++;
		else if (ft_isquote(*begin))
			saved_quote = *begin;
		else if (!b || !ft_isspace(*begin))
			size++;
		else
			b = (ft_isspace(*begin)) ? 1 : 0;
		begin++;
	}
	return (size);
}

/*
** Get data (argument), until separator or end and copy only one space
*/

char	*get_data_one_space(char **str)
{
	char	*data;
	char	*begin;

	while (ft_isspace(**str))
		(*str)++;
	if (!(data = malloc(sizeof(char) * (get_size_one_space(str) + 1))))
		return (NULL);
	begin = data;
	fill_data_one_space(str, &data);
	return (begin);
}
