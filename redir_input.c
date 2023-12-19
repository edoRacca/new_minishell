/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:18:14 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/19 13:40:48 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	input_continue_2(t_env *e, int fd, pid_t pid)
{
	if (pid == 0)
	{
		dup2(fd, STDIN_FILENO);
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
	else
		waitpid(pid, NULL, 0);
	e->exit = 1;
}

void	input_continue(t_env *e, int fd)
{
	pid_t	pid;

	if (e->tokens->type == INPUT)
		return ;
	if (e->tokens->type != BUILT && \
	e->tokens->type != NOBUILT && e->tokens->type != PATH)
	{
		cmd_notfound(e);
		return ;
	}
	if (e->tokens->type == NOBUILT)
	{
		redir_free(e);
		alloc_flagmatrix(e);
		alloc_cmd_path(e);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		e->exit = 1;
		exiting(e, 1);
	}
	else
		input_continue_2(e, fd, pid);
}
