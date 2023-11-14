/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:10:55 by eraccane          #+#    #+#             */
/*   Updated: 2022/11/16 17:22:57 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>

int	ft_nlen(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		++i;
	while (n)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*dig;
	int		len;
	char	*str;

	dig = "0123456789";
	len = ft_nlen(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = 0;
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
	}
	while (n)
	{
		if (n > 0)
			str[--len] = dig[n % 10];
		else
			str[--len] = dig[n % 10 * -1];
		n /= 10;
	}
	return (str);
}
