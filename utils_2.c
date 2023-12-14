/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 23:42:07 by eraccane          #+#    #+#             */
/*   Updated: 2023/11/30 17:22:11 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* NOTE
** 0 $ not found
** 1 $ found
*/
int	find_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

/* NOTE
** 1 found
** 0 not found
*/
int	check_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

/* NOTE
** 1 correct
** 0 incorrect
*/
int	is_all_alpha(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[i]) == 0)
		return (0);
	i++;
	while (str[i] != '\0' || str[i] != '=')
	{
		if (ft_isalnum(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

/* NOTE
** return the end position of variable name to export (position of '=')
** -1 if names are not matching
** A number if they are matching
*/
int	exp_var_name(char *var, char *newvar)
{
	int	i;

	i = 0;
	while (var[i] != '=')
	{
		if (var[i] != newvar[i])
			return (-1);
		i++;
	}
	if (var[i] == newvar[i])
		return (i);
	else
		return (-1);
}

int	env_var_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] >= 'A' && str[i] <= 'Z' && str[i] != '\0')
		i++;
	return (i);
}
