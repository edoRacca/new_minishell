/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_functions_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:43:38 by eraccane          #+#    #+#             */
/*   Updated: 2023/11/21 19:04:35 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		printf("\ttype:\t%d\n", tokens->token_type);
		tokens = tokens->next;
		i++;
	}
}