/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_trunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:52:18 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/13 23:50:45 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_redir(t_env *e, char *filename, int type)
{
	int	fd;

	if (type == TRUNC)
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else if (type == APPEND)
		fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (fd < 0)
	{
		e->exit_status = 1;
		perror("open");
		exiting(e, 0);
	}
	dup2(fd, 1);
	close(fd);
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
