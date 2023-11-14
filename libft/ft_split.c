/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 09:39:23 by eraccane          #+#    #+#             */
/*   Updated: 2022/11/16 17:53:45 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

static size_t	ft_lenalloc(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			++i;
			while (*s && *s != c)
				++s;
		}
		else
			++s;
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	i;
	size_t	l;

	if (!s)
		return (NULL);
	i = 0;
	str = malloc(sizeof(char *) * (ft_lenalloc(s, c) + 1));
	if (!str)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			l = 0;
			while (*s && *s != c && ++l)
				++s;
			str[i++] = ft_substr(s - l, 0, l);
		}
		else
			++s;
	}
	str[i] = 0;
	return (str);
}
