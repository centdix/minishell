/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_one_space.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 12:49:35 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/12 17:04:44 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Add the size of the envv_variable to int *size
*/

int		add_size_one_space(char **ptr, int *size)
{
	int		ret;

	if ((*((*ptr) - 1)) != '\\' && *(*ptr) == '$' &&
(!ft_isalpha((*((*ptr) + 1))) ||
!ft_isdigit(*((*ptr) + 1)) || (*((*ptr) + 1)) == '_'))
	{
		++(*ptr);
		if ((ret = count_envv_variable(&(*ptr))) < 0)
			return (-1);
		(*size) += ret;
	}
	else if (++(*size))
		(*ptr)++;
	return (0);
}

/*
** Add one or multiply char on the data pointer
*/

int		add_chars_one_space(char **data, char **str)
{
	if ((*((*str) - 1)) != '\\' && *(*str) == '$' &&
(!ft_isalpha((*((*str) + 1))) ||
!ft_isdigit(*((*str) + 1)) || (*((*str) + 1)) == '_'))
	{
		++(*str);
		if (add_envv_and_move(data, str) < 0)
			return (-1);
	}
	else
		*(*data)++ = *(*str)++;
	return (0);
}

/*
** Fill data for data_one_space
*/

int		fill_data_one_space(char **str, char **data)
{
	char	saved_quote;

	saved_quote = 0;
	while (!ft_isseparator(**str) && **str)
	{
		if (**str == '\\')
			*(*data)++ = *(*str)++;
		if (saved_quote && *(*str) == saved_quote && (*str)++)
			saved_quote = 0;
		else if (saved_quote)
		{
			if (add_chars_one_space(data, str) < 0)
				return (-1);
		}
		else if (ft_isquote(*(*str)))
			saved_quote = *(*str)++;
		else if (!ft_isspace(*(*str)) || (*((*str) + 1) &&
!ft_isspace(*((*str) + 1))))
		{
			if (add_chars_one_space(data, str) < 0)
				return (-1);
		}
		else
			(*str)++;
	}
	*(*data) = '\0';
	return (0);
}

/*
** Get size to malloc for data_one_space
*/

int		get_size_one_space(char *ptr)
{
	int		size;
	char	saved_quote;

	size = 0;
	saved_quote = 0;
	while (!ft_isseparator(*ptr) && *ptr)
	{
		if (*ptr == '\\' && ++size)
			ptr++;
		if (saved_quote && *ptr == saved_quote && ptr++)
			saved_quote = 0;
		else if (saved_quote)
		{
			if (add_size_one_space(&ptr, &size) < 0)
				return (-1);
		}
		else if (ft_isquote(*ptr))
			saved_quote = *ptr++;
		else if (!ft_isspace(*ptr) || (*(ptr + 1) && !ft_isspace(*(ptr + 1))))
		{
			if (add_size_one_space(&ptr, &size) < 0)
				return (-1);
		}
		else
			ptr++;
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
	int		size;

	while (ft_isspace(**str))
		(*str)++;
	size = get_size_one_space(*str);
	if (!(data = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ptr = data;
	if (fill_data_one_space(str, &ptr) < 0)
		return (NULL);
	return (data);
}
