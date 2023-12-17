/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 10:52:17 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/16 10:52:34 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_redirection(t_env *e)
{
	t_token	*tokens;

	e->count_redir = 0;
	tokens = start_token(e->tokens);
	while (tokens != NULL)
	{
		if (tokens->type == APPEND || tokens->type == TRUNC || \
		tokens->type == INPUT || tokens->type == HDOC)
			if (redir_between(e) == 0)
				e->count_redir++; 
		tokens = tokens->next;
	}
	return (e->count_redir);
}