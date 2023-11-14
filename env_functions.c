/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 22:51:29 by eraccane          #+#    #+#             */
/*   Updated: 2023/11/14 19:04:16 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** NOTE - env line is copied in e->env line
*/
void    copy_env_line(char *dest, char *src)
{
    int i;

    i = 0;
    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

/*
** NOTE - find enviroment matrix size
*/
int	size_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

/*
** NOTE - copy enviroment matrix into e->env
*/
void	copy_env(t_env *e, char **env)
{
	int	i;

	i = 0;
	e->env = (char **)malloc(sizeof(char *) * size_env(env) + 1);
	while (env[i])
	{
		e->env[i] = (char *)malloc(sizeof(char) * ft_strlen(env[i]) + 1);
		copy_env_line(e->env[i], env[i]);
		i++;
	}
    e->env[i] = NULL;
}

void	init_env(t_env *e, char **env)
{
	e->line = NULL;
	copy_env(e, env);
    
}
