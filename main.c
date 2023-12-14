/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 18:14:15 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/14 00:41:42 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	pre_exec_2(t_env *e)
{
	if (invalid_syntax(e) == 1)
			return (0) ;
	if (invalid_pipe(e) == 1)
		return (0);
	else if (search_pipe(e) == 1)
	{
		count_pipe(e);
		if (search_arrows(e) == TRUNC || search_arrows(e) == APPEND || \
		search_arrows(e) == INPUT || search_arrows(e) == HDOC)
			printf("ciao\n");// redirection_pipe(e);
		else
			piping(e);
		e->exit = 1;
	}
	else
		executing(e);
	return (1);
}

void	pre_exec(t_env *e)
{
	t_token	*first;

	e->exit = 0;
	first = find_first_token(e->tokens);
	e->pipe_quotes = 0;
	e->red_quotes = 0;
	e->redir = 0;
	while(e->tokens != NULL && e->exit == 0)
	{
		if (pre_exec_2(e) == 0)
			return ;
		e->tokens = e->tokens->next;
	}
	e->tokens = first;
	e->stdin = dup(STDIN_FILENO);
	e->stdout = dup(STDOUT_FILENO);
}

int	main(int ac, char *av[], char **env)
{
	t_env	*e;

	(void)ac;
	(void)av;
	e = malloc(sizeof(t_env));
	init_env(e, env);
	while(1)
	{
		signals(e);
		e->line = readline("$> ");
		if (e->line == NULL)
			ctrl_d(e);
		parsing(e);
		pre_exec(e);
		if (e->line[0] != '\0' && e->hdoc == 0)
			add_history(e->line);
		if (e->tokens != NULL)
			free_tokens(&e->tokens);
		e->hdoc = 0;
	}
}
