/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 18:59:34 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/13 00:52:05 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_putstr(const char *src)
{
	int		i;
	char	*s;

	i = 0;
	s = (char *)malloc(sizeof(char) * ft_strlen(src) + 1);
	if (src == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		s[i] = src[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_strcpy_n(char *dest, const char *src)
{
	int	i;

	i = 0;
	if (src == NULL)
		return (NULL);
	dest = (char *)malloc(sizeof(char) * ft_strlen(src) + 1);
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	continue_join_n(char *st, char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		st[i] = s1[i];
		i++;
	}
	st[i] = '\n';
	while (s2[j])
		st[i++] = s2[j++];
	st[i] = '\n';
	i++;
	st[i] = 0;
}

char	*alloc_str(char *s)
{
	int		i;
	char	*st;

	i = 0;
	st = (char *)malloc(sizeof(char) * ft_strlen(s) + 1 + 1);
	while (s[i] != '\0')
	{
		st[i] = s[i];
		i++;
	}
	st[i] = '\n';
	i++;
	st[i] = '\0';
	return (st);
}

char	*ft_strjoin_n(char *s1, char *s2)
{
	char	*st;

	if (!s1)
	{
		st = alloc_str(s2);
		return (st);
	}
	else if (!s2)
	{
		st = alloc_str(s1);
		return (st);
	}
	else if (!s1 && !s2)
		return (NULL);
	st = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1 + 2));
	if (st == NULL)
		return (NULL);
	continue_join_n(st, s1, s2);
	return (st);
}
