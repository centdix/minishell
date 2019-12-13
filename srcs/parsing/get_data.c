/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 23:03:25 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/13 09:31:39 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Fill data for special char like ' ', " " or \
*/

int		fill_data_special(char **str, char **data)
{
	if (**str == '\\' && (*str)++)
	{
		*(*data)++ = *(*str)++;
		return (1);
	}
	else if (**str == '\'' && (*str)++)
	{
		while (**str && **str != '\'' && !ft_isseparator(**str))
			*(*data)++ = *(*str)++;
		(*str) += (**str == '\'') ? 1 : 0;
		return (1);
	}
	else if (**str == '\"' && (*str)++)
	{
		while (**str && **str != '\"' && !ft_isseparator(**str))
		{
			if (**str == '\\' && (*str)++)
				*(*data)++ = *(*str)++;
			else if (check_envv_and_move(str, data) < 0)
				return (-1);
		}
		(*str) += (**str == '\"') ? 1 : 0;
		return (1);
	}
	return (0);
}

/*
** Fill data for get_data
*/

int		fill_data(char **str, char **data)
{
	int ret;

	while (**str && !ft_isseparator(**str))
	{
		ret = fill_data_special(str, data);
		if (ret < 0)
			return (-1);
		else if (!ret)
		{
			if (**str && (!ft_isspace(**str) || (*((*str) + 1) &&
	!ft_isspace(*((*str) + 1)))))
			{
				if (check_envv_and_move(str, data) < 0)
					return (-1);
			}
			else
				(*str)++;
		}
	}
	*(*data) = '\0';
	return (0);
}

/*
** Get size of data for special char like ' ', " " or \
*/

int		get_data_size_special(char **str, int *size)
{
	if (*(*str) == '\\' && (*size)++ && ((*str) += (*((*str) + 1)) ? 2 : 1))
		return (1);
	else if (*(*str) == '\'' && (*str)++)
	{
		while (*(*str) && *(*str) != '\'' &&
!ft_isseparator(*(*str)) && ++(*size))
			(*str)++;
		(*str) += (*(*str) == '\'') ? 1 : 0;
		return (1);
	}
	else if (*(*str) == '\"' && (*str)++)
	{
		while (*(*str) && *(*str) != '\"' && !ft_isseparator(*(*str)))
		{
			if (*(*str) == '\\' && ++(*size))
				(*str) += (*((*str) + 1)) ? 2 : 1;
			else if (check_envv_and_size(&(*str), &(*size)) < 0)
				return (-1);
		}
		(*str) += (*(*str) == '\"') ? 1 : 0;
		return (1);
	}
	return (0);
}

/*
** Get size of data for allocation memory in get_data
*/

int		get_data_size(char *str)
{
	int		ret;
	int		size;

	size = 0;
	while (*str && !ft_isseparator(*str))
	{
		ret = get_data_size_special(&str, &size);
		if (ret < 0)
			return (-1);
		else if (!ret)
		{
			if (*str && (!ft_isspace(*str) || (*(str + 1) &&
	!ft_isspace(*(str + 1)))))
			{
				if (check_envv_and_size(&str, &size) < 0)
					return (-1);
			}
			else
				str++;
		}
	}
	return (size);
}

/*
** Replace backslash, env_variables, and quote when it should
*/

char	*get_data(char **str)
{
	char	*data;
	char	*ptr;
	int		size;

	while (ft_isspace(**str))
		(*str)++;
	size = get_data_size(*str);
	if (!(data = malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ptr = data;
	if (fill_data(str, &ptr) < 0)
		return (NULL);
	return (data);
}
