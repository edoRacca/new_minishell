/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_redirect_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 19:38:55 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/18 00:41:42 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* NOTE
** finds out if a file exists and if it can be opened, if not the multiple
** redirection command ends
*/
int	find_file_redir(t_env *e, t_token *start)
{
	int		fd;
	char	*filename;

	filename = start->next->string;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("minishell: %s: No such file or directory\n", filename);
		e->exit = 1;
		return (0);
	}
	close(fd);
	return (1);
}
/* NOTE
** finds out if a redirection tokoens is between quotes
*/
int	mult_redir_between(t_token *tk)
{
	t_token	*tokens;
	t_token	*start;

	tokens = start_token(tk);
	start = start_token(tk);
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
/* NOTE
** multipe redirections that are only input type
*/
void	mult_in_redir(t_env *e, t_token *last_in)
{
	t_token	*start;
	int		i;
	int		fd;

	i = 0;
	start = start_token(e->tokens);
	fd = open(last_in->next->string, O_RDONLY);
	while (i < e->count_redir)
	{
		if (start->type == INPUT &&	mult_redir_between(start) == 0)
		{
			if (find_file_redir(e, start) == 0)
				return ;
			i++;
		}
		else if (start->type == HDOC && mult_redir_between(start) == 0)
		{
			redirect_hdoc(e, 0);
			i++;
		}
		start = start->next;
	}
	input_continue(e, fd);
}

int	multiple_choice(t_env *e, t_token *start)
{
	if (start->type == INPUT &&	mult_redir_between(start) == 0)
	{
		if (find_file_redir(e, start) == 0)
			return (-1);
		return (0);
	}
	else if (start->type == HDOC && mult_redir_between(start) == 0)
	{
		redirect_hdoc(e, 0);
		return (0);
	}
	else if ((start->type == APPEND || start->type == TRUNC) && \
		mult_redir_between(start) == 0)
	{
		create_file_redir(e, start);
		return (0);
	}
	return (1);
}

void	mult_mix_redir(t_env *e, t_token *last_in, t_token *last_out)
{
	int		i;
	t_token	*start;

	i = 0;
	start = start_token(e->tokens);
	while (i < e->count_redir)
	{
		if (multiple_choice(e, start) == -1)
			return ;
		else if (multiple_choice(e, start) == 0)
			i++;
		start = start->next;
	}
	mult_p_process(e, last_in, last_out);
}
