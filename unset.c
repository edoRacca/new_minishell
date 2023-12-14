/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:51:27 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/07 12:02:10 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* NOTE
** check if variable names are the same
*/
int	unset_var_name(char *var_e, char *var)
{
	int	i;

	i = 0;
	while (var_e[i] != '=')
	{
		if (var_e[i] != var[i])
			return (0);
		i++;
	}
	return (1);
}

/* NOTE
** copies all env lines in a temporary env except the line where the
** variable I want to unset is
*/
char	**unset_copy_env(char **env, char **dest, char *var)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i] != NULL)
	{
		if (unset_var_name(env[i], var) == 0)
		{
			dest[j] = (char *)malloc(sizeof(char) * ft_strlen(env[i]) + 1);
			copy_line(dest[j], env[i]);
			j++;
		}
		i++;
	}
	free_matrix(env);
	dest[j] = NULL;
	return (dest);
}

/* NOTE 
** 
*/
void	unset_function(t_env *e)
{
	int		i;
	char	**tmp_e;

	i = 0;
	tmp_e = (char **)malloc(sizeof(char *) * (size_env(e->env) - 1));
	tmp_e = unset_copy_env(e->env, tmp_e, e->tokens->string);
	e->env = (char **)malloc(sizeof(char *) * size_env(tmp_e));
	while (tmp_e[i] != NULL)
	{
		e->env[i] = (char *)malloc(sizeof(char) * ft_strlen(tmp_e[i]) + 1);
		copy_line(e->env[i], tmp_e[i]);
		i++;
	}
	e->env[i] = NULL;
	free_matrix(tmp_e);
	e->exit_status = 0;
}
