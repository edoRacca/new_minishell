/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 11:45:38 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/19 12:26:50 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*find_last_out(t_env *e)
{
	t_token	*tokens;

	tokens = find_last_token(e->tokens);
	while (tokens != NULL && tokens->type != PIPE)
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
	while (tokens != NULL && tokens->type != PIPE)
	{
		if (tokens->type == INPUT || tokens->type == HDOC)
			return (tokens);
		tokens = tokens->prev;
	}
	return (NULL);
}

void	create_file_redir(t_env *e, t_token *start)
{
	int		fd;
	char	*filename;
	int		type;

	filename = start->next->string;
	type = start->type;
	if (type == APPEND)
		fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0666);
	else
		fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd < 0)
	{
		e->exit_status = 1;
		perror("open");
	}
	close(fd);
}

void	mult_out_redir(t_env *e, t_token *last_out)
{
	t_token	*start;
	int		i;

	i = 0;
	start = start_token(e->tokens);
	while (i < e->count_redir)
	{
		if ((start->type == APPEND || start->type == TRUNC) && \
		mult_redir_between(start) == 0)
		{
			create_file_redir(e, start);
			i++;
		}
		start = start->next;
	}
	redir_fork(e, last_out->next->string, last_out->type);
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
	if (last_in == NULL && last_out != NULL)
		mult_out_redir(e, last_out);
	else if (last_out == NULL && last_in != NULL)
		mult_in_redir(e, last_in);	
	else
		mult_mix_redir(e, last_in, last_out);
	e->exit = 1;
}
