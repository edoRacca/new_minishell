/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_redirect_3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 17:30:29 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/18 00:40:46 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mult_c_process(t_env *e, int fd_in, int fd_out, pid_t pid)
{
	if (pid == 0)
	{
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		close(fd_in);
		close(fd_out);
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
}

void	mult_p_process(t_env *e, t_token *last_in, t_token *last_out)
{
	int		fd_in;
	int		fd_out;
	pid_t	pid;

	if (last_in->type == INPUT)
		fd_in = open(last_in->next->string, O_RDONLY);
	fd_out = open(last_out->next->string, O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (e->tokens->type == TRUNC || e->tokens->type == APPEND || \
	e->tokens->type == INPUT || e->tokens->type == HDOC)
		return ;
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
		mult_c_process(e, fd_in, fd_out, pid);
}
