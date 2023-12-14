/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:45:38 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/14 12:31:24 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*find_last_out(t_env *e)
{
	t_token	*tokens;

	tokens = find_last_token(e->tokens);
	while (tokens != NULL)
	{
		if (tokens->type == APPEND || tokens->type == TRUNC)
			return (tokens);
		tokens = tokens->prev;
	}
	return (NULL);
}

t_token	*find_last_in(t_env *e)
{
	t_token	*tokens;

	tokens = find_last_token(e->tokens);
	while (tokens != NULL)
	{
		if (tokens->type == INPUT || tokens->type == HDOC)
			return (tokens);
		tokens = tokens->prev;
	}
	return (NULL);
}

/* TODO aoi
** l'ultimo input riversa verso l'ultimo output
** in caso di inesistenza di input (cat < file) eseguire redirect trunc o 
** redirect append in base all'ultimo redirect
** NOTE :
** vanno creati pero tutti i file subito dopo ogni redirect di output 
** (ciclo for in cui viene creato ogni file e poi dopo rediretto tutto il
** comando sull'ultimo) 
*/
void	multiple_redir(t_env *e)
{
	t_token	*last_in;
	t_token	*last_out;

	last_in = find_last_in(e);
	last_out = find_last_out(e);
	printf("last_in: %s\n\n", last_in->next->string);
	printf("last_out: %s\n\n", last_out->next->string);
	e->exit = 1;
}