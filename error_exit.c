/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:19:02 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/11 19:43:30 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_notfound(t_env *e)
{
	e->exit_status = 127;
	e->exit = 1;
	printf("Command: %s not found\n", start_token(e->tokens)->string);
}

void	fdir_notfound(t_env *e, int type)
{
	if (type == BUILT)
		e->exit_status = 127;
	else
		e->exit_status = 1;
	e->exit = 1;
	printf("%s: '%s': No such file or directory\n", e->tokens->string, \
		e->tokens->next->string);
}

void	too_many_args(t_env *e)
{
	e->exit_status = 1;
	e->exit = 1;
	printf("minishell: %s: too many arguments\n", e->tokens->string);
}

void	too_few_args(t_env *e)
{
	e->exit_status = 1;
	e->exit = 1;
	printf("minishell: %s: too few arguments\n", e->tokens->string);
}

void	exiting(t_env *e, int ex)
{
	if (e->path != NULL)
		free(e->path);
	if (e->cmd_path != NULL)
		free(e->cmd_path);
	if (e->line != NULL)
		free(e->line);
	if (e->env != NULL)
		free_matrix(e->env);
	if (e->tokens != NULL)
	{
		e->tokens = find_first_token(e->tokens);
		free_tokens(&e->tokens);
	}
	if (e->flag_matrix != NULL)
		free_matrix(e->flag_matrix);
	free(e);
	exit(ex);
}
