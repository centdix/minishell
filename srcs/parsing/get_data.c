/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 23:03:25 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/12 02:17:25 by lmartin          ###   ########.fr       */
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
	while (!ft_isspace(*begin) && !ft_isseparator(*begin) && *begin++)
		size++;
	if (!(data = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	begin = data;
	while (!ft_isspace(**str) && !ft_isseparator(**str) && **str)
		*data++ = *(*str)++;
	*data = '\0';
	if (**str)
		(*str)++;
	return (begin);
}

/*
** Fill data for data_one_space
*/

void	fill_data_one_space(char **str, char **data)
{
	char	saved_quote;

	saved_quote = 0;
	while (!ft_isseparator(**str) && **str)
	{
		if (saved_quote && **str == saved_quote)
			saved_quote = 0;
		else if (saved_quote)
			*(*data)++ = *(*str);
		else
		{
			saved_quote = (ft_isquote(**str)) ? **str : 0;
			if (!saved_quote)
			{
				if (!ft_isspace(**str) || (*(*str + 1) && !ft_isspace(*(*str + 1))))
					*(*data)++ = *(*str);
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
	char	*begin;
	size_t	size;
	char	saved_quote;

	begin = *str;
	size = 0;
	saved_quote = 0;
	while (!ft_isseparator(*begin) && *begin)
	{
		if (saved_quote && *begin == saved_quote)
			saved_quote = 0;
		else if (saved_quote)
			size++;
		else if (ft_isquote(*begin))
			saved_quote = *begin;
		else if (!ft_isspace(*begin) || (*(begin + 1) && !ft_isspace(*(begin + 1))))
			size++;
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
	char	*ptr;

	while (ft_isspace(**str))
		(*str)++;
	if (!(data = malloc(sizeof(char) * (get_size_one_space(str) + 1))))
		return (NULL);
	ptr = data;
	fill_data_one_space(str, &ptr);
	return (data);
}
