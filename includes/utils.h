/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmartin <lmartin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 20:16:41 by lmartin           #+#    #+#             */
/*   Updated: 2019/12/13 12:28:53 by lmartin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define ESC_CHAR 27

int		ft_print_clean_str(char *data);

int		ft_free_return(void *ptr);
void	ft_multifree(void *ptr1, void *ptr2, void *ptr3, void *ptr4);
int		ft_setint_and_return(int *ptr, int value);

int		ft_isalpha(char c);
int		ft_isdigit(char c);
int		ft_isquote(char c);
int		ft_isseparator(char c);
int		ft_isspace(char c);

char	*ft_itoa(int n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);

#endif
