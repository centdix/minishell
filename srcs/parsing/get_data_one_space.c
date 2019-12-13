/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_one_space.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 12:49:35 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/13 11:46:22 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Fill data char
*/

int		fill_data_one_space_char(char **str, char **data)
{
	if (**str == '\\' && *((*str) + 1))
	{
		*(*data)++ = *(*str)++;
		*(*data)++ = *(*str)++;
	}
	else if (**str == '\'')
	{
		*(*data)++ = *(*str)++;
		while (**str && **str != '\'' && !ft_isseparator(**str))
			*(*data)++ = *(*str)++;
		if (**str == '\'')
			*(*data)++ = *(*str)++;
	}
	else if (**str == '\"')
	{
		*(*data)++ = *(*str)++;
		while (**str && **str != '\"' && !ft_isseparator(**str))
			*(*data)++ = *(*str)++;
		if (**str == '\"')
			*(*data)++ = *(*str)++;
	}
	else if (check_envv_and_move(str, data) < 0)
		return (-1);
	return (0);
}

/*
** Fill data for get_data
*/

int		fill_data_one_space(char **str, char **data)
{
	while (**str && !ft_isseparator(**str))
	{
		if (**str && (!ft_isspace(**str) || (*((*str) + 1) &&
!ft_isspace(*((*str) + 1)))))
		{
			if (fill_data_one_space_char(str, data) < 0)
				return (-1);
		}
		else
			(*str)++;
	}
	*(*data) = '\0';
	return (0);
}

/*
** Get size of char or ' ' " "
*/

int		get_data_one_space_size_char(char **str, int *size)
{
	if (*(*str) == '\\' && *((*str) + 1))
	{
		(*size) += 2;
		(*str) += 2;
	}
	else if (*(*str) == '\'' && ++(*size) && ++(*str))
	{
		while (*(*str) && *(*str) != '\'' &&
!ft_isseparator(*(*str)) && ++((*size)))
			(*str)++;
		(*str) += (*(*str) == '\'' && ++(*size)) ? 1 : 0;
	}
	else if (*(*str) == '\"' && ++(*size) && ++(*str))
	{
		while (*(*str) && *(*str) != '\"' &&
!ft_isseparator(*(*str)) && ++(*size))
			(*str)++;
		(*str) += (*(*str) == '\"' && ++(*size)) ? 1 : 0;
	}
	else if (check_envv_and_size(&(*str), size) < 0)
		return (-1);
	return (0);
}

/*
** Get size of data for allocation memory in get_data
*/

int		get_data_one_space_size(char *str)
{
	int		size;

	size = 0;
	while (*str && !ft_isseparator(*str))
	{
		if (*str && (!ft_isspace(*str) || (*(str + 1) &&
!ft_isspace(*(str + 1)))))
		{
			if (get_data_one_space_size_char(&str, &size) < 0)
				return (-1);
		}
		else
			str++;
	}
	return (size);
}

/*
** Replace backslash, env_variables, and quote when it should
*/

char	*get_data_one_space(char **str)
{
	char	*data;
	char	*ptr;
	int		size;

	while (ft_isspace(**str))
		(*str)++;
	size = get_data_one_space_size(*str);
	if (!(data = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ptr = data;
	if (fill_data_one_space(str, &ptr) < 0)
		return (NULL);
	return (data);
}
