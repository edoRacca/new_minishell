/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_hdoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:47:18 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/13 01:20:18 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_error_red(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	return (0);
}

char	*update_buffer(char *line, char *buffer)
{
	char	*all;
	char	*buf;

	all = NULL;
	all = ft_strcpy_n(all, buffer);
	buf = ft_strjoin_n(all, line);
	free(all);
	free(buffer);
	return (buf);
}

void	print_hdoc_continue(t_env *e, char *s, int pipe_fd[2], pid_t pid)
{
	if (pid == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		e->hdoc_str = ft_putstr(s);
		cmd_type(e);
		free(s);
		free(e->hdoc_str);
		exiting(e, 1);
	}
	else
	{
		close(pipe_fd[0]);
		write(pipe_fd[1], s, ft_strlen(s));
		close(pipe_fd[1]);
		waitpid(pid, NULL, 0);
	}
	free(s);
}

void	print_redir_hdoc(t_env *e, char *buffer)
{
	int		pipe_fd[2];
	pid_t	pid;
	char	*s;

	s = NULL;
	s = ft_strcpy_n(s, buffer);
	free(buffer);
	if (check_error_red(pipe_fd) == 1)
		return ;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	else
		print_hdoc_continue(e, s, pipe_fd, pid);
}
