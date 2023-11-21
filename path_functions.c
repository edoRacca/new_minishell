/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:01:58 by eraccane          #+#    #+#             */
/*   Updated: 2023/11/21 19:03:44 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
** NOTE - 
** 0 = correct compare / 1 = incorrect compare
*/

int	find_path(char *str)
{
	if (ft_strncmp(str, "PATH", 4) != 0)
		return (1);
	return (0);
}

void	copy_path(t_env *e, int i, int j)
{
	int z;
	int	flag;

	z = 0;
	flag = 0;
	e->path = (char *)malloc(sizeof(char) * ft_strlen(e->env[i]) - 4 + 1);
	while (e->env[i][j] != '\0')
	{
		e->path[z] = e->env[i][j];
		if (e->env[i][j] == 'u' && e->env[i][j + 4] == 'b' && flag == 0)
		{
			cmd_path(e, i, j);
			flag = 1;	
		}
		z++;
		j++;
	}
	e->path[z] = '\0';
}

void	cmd_path(t_env *e, int i, int j)
{
	int z;

	z = 0;
	e->cmd_path = (char *)malloc(sizeof(char) * 12);
	while (e->env[i][j] != ':')
	{
		e->cmd_path[z] = e->env[i][j];
		z++;
		j++;
	}
	e->cmd_path[z] = '/';
	e->cmd_path[z] = '\0';
}

void    search_path(t_env *e)
{
	int	i;
	int	j;

	i = 0;
	while (e->env[i] != NULL)
	{
		j = 5;
		if (find_path(e->env[i]) == 0)
		{
			if (ft_strncmp(&e->env[i][j], "/usr/local/sbin", 16))
			{
				copy_path(e, i, j);
				return ;
			}	
		}
		i++;
	}
}
