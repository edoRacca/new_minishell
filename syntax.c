/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:00:57 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/13 20:21:04 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	search_pipe(t_env *e)
{
	t_token	*start;

	start = start_token(e->tokens);
	while (start != NULL)
	{
		if (start->type == PIPE)
		{
			if (pipe_between(start) == 1)
				return (0);
			else
			{
				e->pipe_quotes = 0;
				return (1);
			}
		}
		start = start->next;
	}
	return (0);
}

int	invalid_pipe(t_env *e)
{
	if (e->tokens->type == PIPE && e->pipe_quotes == 0)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		e->exit = 1;
		e->exit_status = 1;
		return (1);
	}
	return (0);
}

int	invalid_cmd(t_env *e)
{
	t_token	*start;

	start = start_token(e->tokens);
	while (start != NULL)
	{
		if (start->type == PIPE && (start->next == NULL || \
			start->next->type == EMPTY))
		{
			printf("minishell: syntax error near unexpected token `|'\n");
			e->exit = 1;
			e->exit_status = 1;
			return (1);
		}
		start = start->next;
	}
	return (0);
}

int	invalid_syntax(t_env *e)
{
	t_token	*tokens;

	tokens = start_token(e->tokens);
	if (invalid_cmd(e) == 1)
		return (1);
	while (tokens != NULL && tokens->type != PIPE && tokens->type != TRUNC && \
	tokens->type != INPUT && tokens->type != APPEND && tokens->type != HDOC)
		tokens = tokens->next;
	if (tokens == NULL)
		return (0);
	else if (tokens->next == NULL)
	{
		printf("minishell: syntax error near %s\n", tokens->string);
		return (1);
	}
	else if (tokens->next->type == TRUNC || tokens->next->type == APPEND || \
	tokens->next->type == INPUT || tokens->next->type == HDOC)
	{
		printf("minishell: syntax error near %s\n", tokens->string);
		return (1);
	}
	return (0);
}
