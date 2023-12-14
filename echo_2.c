/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 10:36:27 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/13 01:16:38 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	else_quotes_format(t_env *e)
{
	int	i;

	i = 0;
	while (e->tokens->string[i] != '\0')
	{
		if (e->tokens->string[i] != 34 && e->tokens->string[i] != 39)
		{
			if (e->tokens->string[i] == '$')
			{
				echo_expansion(e);
				while ((e->tokens->string[i] >= 'A' && \
				e->tokens->string[i] <= 'Z' && e->tokens->string[i + 1] != '\0') ||\
				e->tokens->string[i] == '$')
					i++;
			}
			else
				printf("%c", e->tokens->string[i]);
		}
		i++;
	}
}

void	check_closure(t_env *e, t_token *start, char quote)
{
	int			cont;
	int			i;
	t_token	*tokens;

	cont = 0;
	i = 0;
	tokens = start_token(start);
	while (tokens != NULL)
	{
		if ((check_quotes(tokens->string) == 1 && cont != 0) || \
		e->flag_quotes == 1)
		{
			while (tokens->string[i] != quote)
				i++;
			if (tokens->string[i] == 34)
				e->quotes = 2;
			else if (tokens->string[i] == 39)
				e->quotes = 1;
			e->flag_quotes = 1;
			return ;
		}
		cont++;
		tokens = tokens->next;
	}
}

void	quotes_format(t_env *e)
{
	int	i;

	i = 0;
	if (e->quotes == 0)
		printf("%s", e->tokens->string);
	else if (e->quotes == 1)
	{
		while (e->tokens->string[i] != '\0')
		{
			if (e->tokens->string[i] != 39)
				printf("%c", e->tokens->string[i]);
			i++;
		}
	}
	else
		else_quotes_format(e);
}

int	check_redir(t_env *e)
{
	if ((e->tokens->type == APPEND || e->tokens->type == INPUT || \
	e->tokens->type == TRUNC || e->tokens->type == HDOC) && \
	redir_between(e) == 0)
		return (1);
	return (0);
}