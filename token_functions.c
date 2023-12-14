/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 23:58:20 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/11 18:59:57 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*find_last_token(t_token *token)
{
	if (!token)
		return (0);
	while (token->next)
		token = token->next;
	return (token);
}

void	addback_token_node(t_token **token, t_token *new)
{
	t_token	*last;

	last = find_last_token(*token);
	if (!last)
		*token = new;
	else
	{
		last->next = new;
		last->next->prev = last;
	}
}

t_token	*new_token_node(char *word)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->string = (char *)malloc(sizeof(char) * ft_strlen(word) + 1);
	if (!token->string)
	{
		free(token);
		return (NULL);
	}
	ft_strlcpy(token->string, word, ft_strlen(word) + 1);
	token->next = NULL;
	token->prev = NULL;
	select_type(token, word);
	return (token);
}

void	init_tokens(t_env *e, char **cmd_line)
{
	int	i;

	i = 0;
	while(cmd_line[i])
	{
		addback_token_node(&e->tokens, new_token_node(cmd_line[i]));
		i++;
	}
}

void	free_tokens(t_token **tokens)
{
	t_token	*temp;

	if (*tokens == NULL)
		return ;
	while (*tokens)
	{
		temp = (*tokens)->next;
		free((*tokens)->string);
		free(*tokens);
		*tokens = temp;
	}
	*tokens = NULL;
}