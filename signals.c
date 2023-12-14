/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:58:18 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/14 11:42:50 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		sig_code;

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		sig_code = 130;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_clear_history();
	}
}

void	signals(t_env *e)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handle_signal);
	if (sig_code == 130)
	{
		e->exit_status = sig_code;
		sig_code = 0;
	}
}

void	ctrl_d(t_env *e)
{
	if (e->path != NULL)
		free(e->path);
	if (e->cmd_path != NULL)
		free(e->cmd_path);
	if (e->line != NULL)
		free(e->line);
	if (e->env != NULL)
		free_matrix(e->env);
	if (e->flag_matrix != NULL)
		free_matrix(e->flag_matrix);
	free(e);
	exit(0);
}

int	signals_hdoc(char *line, char *delimiter, char *buffer)
{
	if (line == NULL)
	{
		printf("minishell: warning: here-document delimited by end-of-file ");
		printf("(wanted '%s')\n", delimiter);
		printf("%s", buffer);
		return (1);
	}
	return (0);
}
