/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 00:23:55 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/13 00:32:18 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	waiting(t_env *e, pid_t pid)
{
	pid_t	child;

	child = waitpid(pid, &e->status, 0);
	if (child == -1)
	{
		perror("waitpid");
		exiting(e, 1);
	}
	else
	{
		e->exit = 1;
		if (WIFEXITED(e->status) == 0)
			e->exit_status = WEXITSTATUS(e->status);
		else
			e->exit_status = 0;
	}
}

void	exec_cmd(t_env *e)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exiting(e, 1);
	}
	else if (pid == 0)
	{
		execve(e->cmd_path, e->flag_matrix, e->env);
		perror("execve");
		exiting(e, 1);
	}
	else
		waiting(e, pid);
}

void	alloc_cmd_path(t_env *e)
{
	char	*path;

	path = NULL;
	path = ft_strcpy_n(path, e->cmd_path);
	free(e->cmd_path);
	e->cmd_path = NULL;
	e->cmd_path = ft_strjoin(path, e->flag_matrix[0]);
	free(path); 
}

/* NOTE
** 
*/
void	alloc_flagmatrix(t_env *e)
{
	t_token	*tokens;
	int		i;

	tokens = start_token(e->tokens);
	i = 1;
	e->flag_matrix = (char **)malloc(sizeof(char *) * (count_flag(e) + 2));
	e->flag_matrix[0] = put_cmd(e, tokens->string);
	tokens = tokens->next;
	while (tokens != NULL && tokens->type != PIPE && tokens->type != APPEND && \
	tokens->type != TRUNC && tokens->type != INPUT && tokens->type != NOBUILT \
	&& tokens->type != HDOC)
	{
		e->flag_matrix[i] = (char *)malloc(sizeof(char) * \
							ft_strlen(tokens->string) + 1);
		copy_line(e->flag_matrix[i], tokens->string);
		i++;
		tokens = tokens->next;
	}
	e->flag_matrix[i] = NULL;
}

void	nobuilt_command(t_env *e)
{
	if (e->flag_matrix != NULL)
		free_matrix(e->flag_matrix);
	alloc_flagmatrix(e);
	alloc_cmd_path(e);
	if (empty_cmd(e) == 0)
		return ;
	else if (e->cmd_path != NULL && access(e->cmd_path, X_OK) == 0 && \
		e->tokens->type == NOBUILT)
		exec_cmd(e);
	else
		cmd_notfound(e);
}
