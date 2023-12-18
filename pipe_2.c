/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 23:47:00 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/18 21:16:09 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*update_pipe(t_env *e)
{
	t_token	*tokens;
	t_token	*last_cmd;

	tokens = start_token(e->tokens);
	while (e->tokens != NULL)
	{
		while (tokens != NULL && tokens->type != PIPE)
			tokens = tokens->next;
		if (tokens == NULL)
			return (last_cmd);
		last_cmd = start_token(tokens);
		if (tokens != NULL)
			return(tokens->next);
	}
	return (last_cmd);
}

void	parent_command(t_env *e)
{
	e->pid_pipe = fork();
	if (e->pid_pipe < 0)
	{
		e->exit = 1;
		perror("fork");
		exiting(e, 1);
	}
	else if (e->pid_pipe == 0)
	{
		execve(e->cmd_path, e->flag_matrix, e->env);
		e->exit = 1;
		perror("execve");
		exiting(e, 1);
	}
	else
		waitpid(e->pid_pipe, NULL, 0);
}

void	parent_process(t_env *e)
{
	if (e->tokens->type == NOBUILT || e->tokens->type == PATH)
	{
		redir_free(e);
		alloc_flagmatrix(e);
		alloc_cmd_path(e);
		if (access(e->cmd_path, X_OK) == 0)
			parent_command(e);
	}
	else
		cmd_type(e);
	close(e->pipe_fd[0]);
	close(e->pipe_fd[1]);
	dup2(e->stdout, STDOUT_FILENO);
	close(e->stdout);
	dup2(e->stdin, STDIN_FILENO);
	close(e->stdin);
}

void	fork_loop(t_env *e)
{
	close(e->pipe_fd[0]);
	dup2(e->pipe_fd[1], STDOUT_FILENO);
	close(e->pipe_fd[1]);
	if (e->tokens->type == NOBUILT || e->tokens->type == PATH)
	{
		redir_free(e);
		alloc_flagmatrix(e);
		alloc_cmd_path(e);
		if (access(e->cmd_path, X_OK) == 0)
		{
			execve(e->cmd_path, e->flag_matrix, e->env);
			perror("execve");
			exiting(e, 1);
		}
		exiting(e, 0);
	}
	else
		cmd_type(e);
	exiting(e, 0);
}
