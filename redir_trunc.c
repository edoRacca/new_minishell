/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_trunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:52:18 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/19 10:55:16 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_redir(t_env *e, char *filename, int type)
{
	if (type == TRUNC)
		e->fd_redir = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else if (type == APPEND)
		e->fd_redir = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (e->fd_redir < 0)
	{
		e->exit_status = 1;
		perror("open");
		exiting(e, 0);
	}
    e->tmp_fd = e->fd_redir;
	dup2(e->fd_redir, 1);
	close(e->fd_redir);
	if (e->cmd_path != NULL)
		if (access(e->cmd_path, X_OK) == 0 && e->tokens->type == NOBUILT)
		{
			execve(e->cmd_path, e->flag_matrix, e->env);
			perror("execve");
			exiting(e, 1);
		}
	cmd_type(e);
	exiting(e, 0);
}

void	redir_fork(t_env *e, char *filename, int type)
{
	pid_t	pid;

	if (e->tokens->type == NOBUILT || e->tokens->type == PATH)
	{
		redir_free(e);
		alloc_flagmatrix(e);
		alloc_cmd_path(e);
		if (access(e->cmd_path, X_OK) == -1)
			e->exit_status = 1;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		e->exit = 1;
		exiting(e, 1);
	}
	else if (pid == 0)
		fork_redir(e, filename, type);
	else
		waiting(e, pid);
	e->exit = 1;
}
