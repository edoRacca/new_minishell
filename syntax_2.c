/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:06:21 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/12 17:51:43 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_closure_redir(t_env *e, t_token *start, char quotes)
{
	int		i;
	t_token	*tokens;
	int		cont;

	tokens = start_token(start);
	i = 0;
	cont = 0;
	while (tokens != NULL)
	{
		if (tokens->type == APPEND || tokens->type == INPUT || \
		tokens->type == TRUNC)
			e->red_quotes = 1;
		if (check_quotes(tokens->string) == 1 && cont != 0)
		{
			while (tokens->string[i] != quotes && tokens->string[i] != '\0')
				i++;
			if (tokens->string[i] == quotes)
				return (1);
		}
		cont++;
		tokens = tokens->next;
	}
	return (0);
}

t_token	*redir_in_quotes(t_env *e, t_token *tokens, int i)
{
	char	quotes;

	e->quotes_open = 1;
	quotes = quote_type(tokens->string);
	while (tokens->string[i] != quotes && tokens->string[i] != '\0')
		i++;
	if (check_quotes_closed(tokens->string, i) == 1)
	{
		e->quotes_open = 0;
		return (tokens);
	}
	if (check_if_open(tokens, i) == 0)
	{
		e->quotes_open = 0;
		return (tokens);
	}
	else
	{
		tokens = tokens->next;
		while (tokens != NULL && check_quotes_red(tokens->string, quotes) == 0)
		{
			if (tokens->type == INPUT || tokens->type == TRUNC || \
			tokens->type == APPEND)
				e->redir = 0;
			tokens = tokens->next;
		}
		if (tokens != NULL && check_quotes_red(tokens->string, quotes) == 1)
		{
			e->quotes_open = 0;
			return (tokens);
		}
	}
	return (NULL);
}

/* NOTE
** Function that finds out if quotes are closed between redirection character
** 
*/
t_token *quotes_redirect(t_env *e, t_token *start)
{
	t_token	*tokens;

	tokens = start_token(start);
	e->quotes_open = 0;
	while (tokens != NULL)
	{
		if ((tokens->type == INPUT || tokens->type == TRUNC || \
			tokens->type == APPEND || tokens->type == HDOC ) && \
			e->quotes_open == 0)
		{
			e->redir = 1;
			return (tokens);
		}
		if (check_quotes(tokens->string) == 1)
			tokens = redir_in_quotes(e, tokens, 0);
		if (tokens != NULL)
			tokens = tokens->next;
	}
	return (tokens);
}

int	check_closure_pipe(t_env *e, t_token *start, char quotes)
{
	int		i;
	t_token	*tokens;
	int		cont;

	tokens = start_token(start);
	i = 0;
	cont = 0;
	while (tokens != NULL)
	{
		if (check_quotes(tokens->string) == 1 && cont != 0)
		{
			while (tokens->string[i] != quotes && tokens->string[i] != '\0')
				i++;
			if (tokens->string[i] == quotes)
			{
				e->pipe_quotes = 1;
				return (1);
			}
		}
		cont++;
		tokens = tokens->next;
	}
	return (0);
}
