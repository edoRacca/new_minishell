/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:59:32 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/07 12:02:10 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* NOTE
** it copies env into a temporary temp adding the new variable setted in str 
*/
char	**copy_env_temp(char **env, char **dest, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i] != NULL)
	{
		dest[j] = (char *)malloc(sizeof(char) * ft_strlen(env[i]) + 1);
		copy_line(dest[j], env[i]);
		i++;
		j++;
	}
	dest[j] = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	copy_line(dest[j], str);
	j++;
	dest[j] = NULL;
	return (dest);
}

/* NOTE
** Copies temporary env into env variable malloc'd for the new variable
*/
char	**alloc_diff_var(char **env, char **tmp_e, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i] != NULL)
	{
		if (exp_var_name(env[i], str) != -1)
		{
			tmp_e[j] = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
			copy_line(tmp_e[j], str);
		}
		else
		{
			tmp_e[j] = (char *)malloc(sizeof(char) * ft_strlen(env[i]) + 1);
			copy_line(tmp_e[j], env[i]);
		}
		i++;
		j++;
	}
	tmp_e[j] = NULL;
	return (tmp_e);
}

void	over_exp_var(t_env *e, char *str)
{
	char	**tmp_e;
	int		i;

	tmp_e = (char **)malloc(sizeof(char *) * (size_env(e->env)));
	tmp_e = alloc_diff_var(e->env, tmp_e, str);
	free_matrix(e->env);
	e->env = (char **)malloc(sizeof(char *) * (size_env(tmp_e)));
	i = 0;
	while (tmp_e[i] != NULL)
	{
		e->env[i] = (char *)malloc(sizeof(char) * ft_strlen(tmp_e[i]) + 1);
		copy_line(e->env[i], tmp_e[i]);
		i++;
	}
	e->env[i] = NULL;
	free_matrix(tmp_e);
}