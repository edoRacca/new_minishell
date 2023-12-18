/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 23:07:57 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/18 20:54:37 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_open(t_token *tokens, int start)
{
	char	quotes;

	quotes = tokens->string[start];
	start++;
	while (tokens != NULL)
	{
		while (tokens->string[start] != '\0' && tokens->string[start] != quotes)
			start++;
		if (tokens->string[start] != '\0' && tokens->string[start] == quotes)
			return (1);
		start = 0;
		tokens = tokens->next;
	}
	return (0);
}

int	is_redir_inquote(char *str)
{
	if (ft_strlen(str) == 3)
	{
		if (str[0] == str[2] && (str[1] == '>' || str[1] == '<'))
			return (1);
	}
	else if (ft_strlen(str) == 4)
	{
		if (str[0] == str[3] && ((str[1] == '>' && str[2] == '>') || \
		(str[1] == '<' && str[2] == '<')))
			return (1);
	}
	return (0);
}

int	redir_between(t_env *e)
{
	t_token	*tokens;
	t_token	*start;

	tokens = start_token(e->tokens);
	start = start_token(e->tokens);
	if (is_redir_inquote(tokens->string) == 1)
		return (1);
	while (tokens != NULL && check_quotes(tokens->string) == 0)
		tokens = tokens->next;
	while (start != NULL && check_quotes(start->string) == 0)
		start = start->prev;
	if (start != NULL && tokens != NULL)
		return (1);
	else
		return (0);
}

int	last_redir(t_token *tokens)
{
	while (tokens != NULL && tokens->type != PIPE)
	{
		if (tokens->type == INPUT || tokens->type == APPEND || \
			tokens->type == TRUNC)
			return (0);
		tokens = tokens->next;
	}
	return (1);
}

int	check_quotes_red(char *str, char quotes)
{
	int	i;

	i = 0;
	while (str[i] != quotes && str[i] != '\0')
		i++;
	if (str[i] == quotes)
		return (1);
	else
		return (0);
}
