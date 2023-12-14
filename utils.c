/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:07:33 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/11 00:20:28 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		printf("|%s|\n", matrix[i]);
		i++;
	}
}

void	free_matrix(char **str)
{
	int i;
	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
		free(str[i--]);
	free(str);
}

//1 correct compare - 0 incorrect compare
int	str_cmp(char *s1, char *s2)
{
	int	j;

	j = 0;
	while (s1[j] != 0 && s2[j] != 0)
	{
		if (s1[j] != s2[j])
			return (0);
		j++;
	}
	if (s1[j] == 0 && s2[j] == 0)
		return (1);
	return (0);
}


// 1 closed - 0 not closed
// Must pass to 'start' the position of the first quote ('/")
int	check_quotes_closed(char *str, int start)
{
	char	quote;

	quote = str[start];
	if (str[start + 1] == '\0')
		return (0);
	start++;
	while (str[start] != '\0')
	{
		if (str[start] == quote)
			return (1);
		start++;
	}
	return (0);
}

// 1 there are quotes - 0 no quotes
int	check_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 34 || str[i] == 39)
			return (1);
		i++;
	}
	return (0);
}