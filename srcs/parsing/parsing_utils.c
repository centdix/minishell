/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 11:48:49 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/12 14:22:24 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Add an environment value to a char and move the two pointer (one for the
** size of the value and the other the size of his key)
*/

int		add_envv_and_move(char **ptr, char **str)
{
	char	*tmp;
	char	*value;

	if (!(tmp = strdup_to_sep(str)))
		return (-1);
	value = get_env_value(g_envv, tmp);
	if (value)
		put_str_to_str(&(*ptr), value);
	(*str) += ft_strlen(tmp);
	free(tmp);
	return (0);
}

/*
** Count the size of a envv variable in a string pointed by ptr and move pointer
*/

int		count_envv_variable(char **ptr)
{
	char	*tmp;
	char	*value;

	if (!(tmp = strdup_to_sep(ptr)))
		return (-1);
	value = get_env_value(g_envv, tmp);
	free(tmp);
	return ((value) ? ft_strlen(value) : 0);
}

/*
** Put src into dst, move the pointer
** Careful : Be sure to have allocated enought space
*/

void	put_str_to_str(char **dst, char *src)
{
	while (*src)
		*(*dst)++ = *src++;
}

/*
** Allocate a new string which stop to space, separator or end of the ptr string
*/

char	*strdup_to_sep(char **begin)
{
	char	saved_char;
	char	*ptr;
	char	*str;

	ptr = *begin;
	while (*ptr && !ft_isspace(*ptr) && !ft_isseparator(*ptr))
		ptr++;
	saved_char = *ptr;
	*ptr = '\0';
	if (!(str = ft_strdup(*begin)))
		return (NULL);
	*ptr = saved_char;
	return (str);
}
