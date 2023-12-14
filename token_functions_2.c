/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_functions_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:43:38 by eraccane          #+#    #+#             */
/*   Updated: 2023/11/29 19:22:59 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* NOTE
** returns the start token passed
*/
t_token	*start_token(t_token *tokens)
{
	return (tokens);
}

t_token	*find_first_token(t_token *token)
{
	if (!token)
		return (NULL);
	while (token->prev != NULL)
		token = token->prev;
	return (token);
}

void	print_tokens(t_token *tokens)
{
	int	i;

	if (!tokens)
		printf("tokens[0]:\tNULL\n");
	i = 0;
	while (tokens)
	{
		printf("tokens[%d]:\n", i);
		printf("\tstring:\t\t%s\n", tokens->string);
		printf("\ttype:\t%d\n", tokens->type);
		tokens = tokens->next;
		i++;
	}
}