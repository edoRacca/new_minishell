/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 11:41:45 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/18 13:28:25 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*update_pipe_redir(t_env *e)
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

int	find_red_inpipe(t_env *e)
{
	t_token	*start;
	int		count;

	start = start_token(e->tokens);
	count = 0;
	while (start->type != PIPE && start != NULL)
	{
		if (start->type == APPEND || start->type == TRUNC || \
		start->type == INPUT)
			count++;
		start = start->next;
	}
	return (count);
}

void	pipe_redir_fork(t_env *e)
{
	close(e->pipe_fd[0]);
	dup2(e->pipe_fd[1], STDOUT_FILENO);
	close(e->pipe_fd[1]);
	if (find_red_inpipe(e) > 0)
	{
		
	}
}

void	mult_pipe_redir(t_env *e)
{
	e->pid_pipe = fork();
	if (e->pid_pipe < 0)
	{
		perror("fork");
		exiting(e, 1);
	}
	else if (e->pid_pipe == 0)
		pipe_redir_fork(e);
	else
	{
		close(e->pipe_fd[1]);
		dup2(e->pipe_fd[0], STDIN_FILENO);
		close(e->pipe_fd[0]);
		waitpid(e->pid_pipe, &e->status, 0);
		if (WIFEXITED(e->status))
			e->exit = WEXITSTATUS(e->status);
	}
}

void	pipe_redirection(t_env *e)
{	
	int			i;

	i = 0;
	while (i < e->count_pipe)
	{
		printf("tokens: %s\n\n", e->tokens->string);
		if (pipe(e->pipe_fd) == -1)
		{
			perror("pipe");
			exiting(e, 1);
		}
		// mult_pipe_redir(e);
		i++;
		e->tokens = update_pipe(e);
	}
	// parent process
	// dup2(e->stdin, STDIN_FILENO);
	// close(e->stdin);
	// dup2(e->stdout, STDOUT_FILENO);
	e->exit = 1;
}
