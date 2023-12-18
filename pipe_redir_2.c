/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 16:42:47 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/18 19:29:12 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipered_p_process(t_env *e)
{
	if (count_red_inpipe(e) > 0)
        executing(e);
    else if (e->tokens->type == NOBUILT || e->tokens->type == PATH)
    {
        redir_free(e);
		alloc_flagmatrix(e);
		alloc_cmd_path(e);
		if (access(e->cmd_path, X_OK) == 0)
		{
			execve(e->cmd_path, e->flag_matrix, e->env);
			perror("execve");
			exiting(e, 1);
		}
		exiting(e, 0);
    }
    else
		cmd_type(e);
	close(e->pipe_fd[0]);
	close(e->pipe_fd[1]);
}
