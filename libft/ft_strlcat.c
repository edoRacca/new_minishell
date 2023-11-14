/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 11:07:38 by eraccane          #+#    #+#             */
/*   Updated: 2022/10/24 11:37:18 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	r;

	if (!dest)
		return (0);
	i = 0;
	while (*dest && i < size)
	{
		++dest;
		++i;
	}
	r = ft_strlcpy(dest, src, size - i);
	return (r + i);
}
