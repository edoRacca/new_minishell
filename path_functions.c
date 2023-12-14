/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 18:01:58 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/09 18:00:32 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
** NOTE - 
** 0 = correct strncmp / 1 = incorrect strncmp
*/

int	find_path(char *str)
{
	if (ft_strncmp(str, "PATH", 4) != 0)
		return (0);
	return (1);
}

void	set_cmdpath(t_env *e, int i, int j)
{
	int	z;

	z = 0;
	if (e->cmd_path != NULL)
		free(e->cmd_path);
	e->cmd_path = (char *)malloc(sizeof(char) * 10 + \
	ft_strlen(find_last_token(e->tokens)->string));
	while (e->env[i][j] != ':')
	{
		e->cmd_path[z] = e->env[i][j];
		z++;
		j++;
	}
	e->cmd_path[z] = '/';
	z++;
	e->cmd_path[z] = '\0';
}

void	cmd_path(t_env *e)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while (e->env[i] != NULL)
	{
		if (find_path(e->env[i]) == 1)
		{
			while (e->env[i][j] != '\0')
			{
				if (e->env[i][j] == 'u' && e->env[i][j + 4] == 'b' && \
					(e->tokens->type == NOBUILT || \
					e->tokens->type == PATH))
				{
					set_cmdpath(e, i, j - 1);
					return ;
				}
				j++;
			}	
		}
		i++;
	}
}

void	copy_path(t_env *e, int i, int j)
{
	int z;

	z = 0;
	e->path = (char *)malloc(sizeof(char) * ft_strlen(e->env[i]) - 4 + 1);
	while (e->env[i][j] != '\0')
	{
		e->path[z] = e->env[i][j];
		z++;
		j++;
	}
	e->path[z] = '\0';
}

void    search_path(t_env *e)
{
	int	i;
	int	j;

	i = 0;
	while (e->env[i] != NULL)
	{
		j = 5;
		if (find_path(e->env[i]) == 1)
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
