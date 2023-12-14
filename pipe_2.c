/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 23:47:00 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/14 01:05:18 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pipe(t_env *e)
{
	t_token	*tokens;

	tokens = start_token(e->tokens);
	while (e->tokens != NULL)
	{
		while (tokens != NULL && tokens->type != PIPE && \
		tokens->type != TRUNC && tokens->type != APPEND && \
		tokens->type != INPUT)
			tokens = tokens->next;
		if (e->tokens == NULL)
			return ;
		if (e->tokens->type == TRUNC || e->tokens->type == INPUT || \
		e->tokens->type == APPEND)
			return ;
		if (e->tokens != NULL)
			e->tokens = e->tokens->next;
	}
}

/* FIXME
** SEGFAULT quando va a controllare il token per l'ultimo processo
** l'errore viene da 'update_pipe' che restituisce un token NULL che appunto
** ha attributi. Va cambiato il return in caso di insistenza di altre pipe
** in modo da far restituire l'ultimo comando subito dopo l'ultima pipe
*/
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
		if (access(e->cmd_path, X_OK) == -1)
			parent_command(e);
		exiting(e, 0);
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
		if (access(e->cmd_path, X_OK) == -1)
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
