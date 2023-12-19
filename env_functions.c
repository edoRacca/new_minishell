/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 22:51:29 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/19 11:15:14 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
** NOTE - env line is copied in e->env line
*/
void    copy_line(char *dest, char *src)
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
	while (env[i] != NULL)
		i++;
	return (i + 1);
}

/*
** NOTE - copy enviroment matrix into e->env
*/
void	copy_env(t_env *e, char **env)
{
	int	i;

	i = 0;
	e->env = (char **)malloc(sizeof(char *) * size_env(env));
	while (env[i] != NULL)
	{
		e->env[i] = (char *)malloc(sizeof(char) * ft_strlen(env[i]) + 1);
		copy_line(e->env[i], env[i]);
		i++;
	}
    e->env[i] = NULL;
}

void	print_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

void	init_env(t_env *e, char **env)
{
	copy_env(e, env);
	e->line = NULL;
	search_path(e);
	e->cmd_path = NULL;
	e->flag_matrix = NULL;
	e->exit_status = 0;
	e->quotes = -1;
	e->hdoc = 0;
	e->tokens = NULL;
    e->tmp_fd = -1;
	e->stdin = dup(STDIN_FILENO);
	e->stdout = dup(STDOUT_FILENO);
}
