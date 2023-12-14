/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:49:45 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/14 11:18:41 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	multiple_pipe(t_env *e)
{
	e->pid_pipe = fork();
	if (e->pid_pipe < 0)
	{
		perror("fork");
		exiting(e, 1);
	}
	else if (e->pid_pipe == 0)
		fork_loop(e);
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

void	piping(t_env *e)
{
	int	i;

	i = 0;
	e->exit_status = 0;
	while (i < e->count_pipe)
	{
		if (pipe(e->pipe_fd) == -1)
		{
			perror("pipe");
			exiting(e, 1);
		}
		multiple_pipe(e);
		i++;
		e->tokens = update_pipe(e);
	}
	parent_process(e);
	dup2(e->stdin, STDIN_FILENO);
	close(e->stdin);
	dup2(e->stdout, STDOUT_FILENO);
}

int	is_pipe_inquote(char *str)
{
	if (ft_strlen(str) == 3)
		if (str[0] == str[2] && str[1] == '|')
			return (1);
	return (0);
}

int	pipe_between(t_token *tk)
{
	t_token	*tokens;
	t_token	*start;

	tokens = start_token(tk);
	start = start_token(tk);
	if (is_pipe_inquote(tokens->string) == 1)
		return (1);
	while (tokens != NULL && check_quotes(tokens->string) == 0)
		tokens = tokens->next;
	while (start != NULL && check_quotes(start->string) == 0)
		start = start->prev;
	if (start != NULL && tokens != NULL)
		return (1);
	else
		return (0);
}

int	count_pipe(t_env *e)
{
	t_token	*tokens;

	e->count_pipe = 0;
	tokens = start_token(e->tokens);
	while (tokens != NULL)
	{
		if (tokens->type == PIPE)
			if (pipe_between(tokens) == 0)
				e->count_pipe++; 
		tokens = tokens->next;
	}
	return (e->count_pipe);
}
