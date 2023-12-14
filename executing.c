/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 20:12:06 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/12 11:53:17 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	last_built_nobuilt(t_env *e)
{
	if (str_cmp(e->tokens->string, "echo"))
	{
		if (e->tokens->next == NULL)
		{
			printf("\n");
			return ;
		}
		e->tokens = e->tokens->next;
		if (str_cmp(e->tokens->string, "-n") && \
			e->tokens->next == NULL)
			return ;
		if (str_cmp(e->tokens->string, "-n"))
		{
			e->tokens = e->tokens->next;
			echo_cmd(e);
		}
		else
		{
			echo_cmd(e);
			printf("\n");
		}
		e->exit_status = 0;
	}
	else
		nobuilt_command(e);
}

void	other_builtin_cmd(t_env *e)
{
	if (str_cmp(e->tokens->string, "cd") == 1 && \
		e->tokens->next != NULL && e->tokens->next->string != NULL)
	{
		if (chdir(e->tokens->next->string) == -1)
		{
			e->exit = 1;
			perror("cd");
		}
		return ;
	}
	else if (str_cmp(e->tokens->string, "cd") == 1)
		return ;
	else if (str_cmp(e->tokens->string, "unset") == 1)
	{
		if (e->tokens->next == NULL)
		{
			e->exit = 1;
			e->exit_status = 0;
			return ;
		}
		e->tokens = e->tokens->next;
		unset_function(e);
	}
	else
		last_built_nobuilt(e);
}

void	builtin_cmd(t_env *e)
{
	char	cwd[1024];

	if (str_cmp(e->tokens->string, "pwd"))
	{
		if (getcwd(cwd, 1024) != NULL)
			printf("%s\n", cwd);
		else
		{
			e->exit = 1;
			perror("pwd");
		}
		return ;
	}
	else if (str_cmp(e->tokens->string, "env") == 1)
	{
		if (e->path == NULL)
			cmd_notfound(e);
		else if (e->tokens->next && e->tokens->next->string != NULL && \
		e->redir == 0)
			fdir_notfound(e, e->tokens->type);
		else
			print_env(e->env);
	}
	else
		other_builtin_cmd(e);
}

void	cmd_type(t_env *e)
{
	if (str_cmp(e->tokens->string, "export"))
	{
		if (e->tokens->next == NULL)
		{
			too_few_args(e);
			return ;
		}
		e->tokens = e->tokens->next;
		export_function(e);
		return ;
	}
	else if (str_cmp(e->tokens->string, "history"))
	{
		add_history(e->line);
		print_history();
	}
	else
		builtin_cmd(e);
}

void	executing(t_env *e)
{
	if (str_cmp(e->tokens->string, "exit") == 1 && e->exit == 0)
		exiting(e, 0);
	else if (search_arrows(e) == TRUNC && e->redir == 1)
		redirect_trunc(e);
	else if (search_arrows(e) == APPEND && e->redir == 1)
		redirect_append(e);
	else if (search_arrows(e) == INPUT && e->redir == 1)
		redirect_input(e);
	else if (search_arrows(e) == HDOC && e->redir == 1)
		redirect_hdoc(e);
	else if (e->tokens->type == BUILT || \
		e->tokens->type == NOBUILT || e->tokens->type == PATH)
		cmd_type(e);
	else
		cmd_notfound(e);
}
