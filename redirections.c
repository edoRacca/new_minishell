/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 16:50:41 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/16 10:56:12 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hdoc_condition(t_env *e, char *buffer, int type)
{
	if (type == 1)
		print_redir_hdoc(e, buffer);
	else
		free(buffer);
}

void	redirect_trunc(t_env *e)
{
	char	*filename;
	int		fd;

	if (e->tokens->type != NOBUILT && e->tokens->type != BUILT && \
	e->tokens->type != TRUNC)
	{
		cmd_notfound(e);
		return ;
	}
	filename = find_filename(e);
	if (find_first_token(e->tokens)->type == TRUNC)
	{
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (fd < 0)
		{
			e->exit_status = 1;
			perror("open");
		}
		close(fd);
		e->exit = 1;
	}
	else
		redir_fork(e, filename, TRUNC);
}

void	redirect_append(t_env *e)
{
	char	*filename;
	int		fd;

	if (e->tokens->type != NOBUILT && e->tokens->type != BUILT && \
		e->tokens->type != TRUNC)
	{
		cmd_notfound(e);
		return ;
	}
	filename = find_filename(e);
	if (find_first_token(e->tokens)->type == APPEND)
	{
		fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (fd < 0)
		{
			e->exit_status = 1;
			perror("open");
		}
		close(fd);
		e->exit = 1;
	}
	else
		redir_fork(e, filename, APPEND);
}

void	redirect_input(t_env *e)
{
	int		fd;
	char	*filename;

	filename = find_filename(e);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		e->exit = 1;
		return ;
	}
	input_continue(e, fd);
	e->exit = 1;
	close(fd);
}

void	redirect_hdoc(t_env *e, int type)
{
	char	*delim;
	char	*line;
	char	*buffer;

	delim = find_delim(e);
	line = NULL;
	buffer = NULL;
	e->hdoc = 1;
	while (1)
	{
		line = readline("heredoc> ");
		signals(e);
		if (signals_hdoc(line, delim, buffer) == 1)
			break ;
		else if (str_cmp(delim, line) == 1)
		{
			hdoc_condition(e, buffer, type);
			break ;
		}
		else
			buffer = update_buffer(line, buffer);
	}
	e->exit = 1;
}
