/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 16:43:58 by fgoulama          #+#    #+#             */
/*   Updated: 2019/12/17 19:51:29 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*result;
	size_t			s_len;

	s_len = s ? ft_strlen(s) : 0;
	if (start >= s_len)
		len = 0;
	if (!(result = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (s[start + i] != '\0' && i < len)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
