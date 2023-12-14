/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 10:58:38 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/12 17:50:05 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	quote_type(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 34 && str[i] != 39 && str[i] != '\0')
		i++;
	if (str[i] != '\0')
		return (str[i]);
	else
		return (0);
}

void	redir_free(t_env *e)
{
	if (e->flag_matrix != NULL)
		free_matrix(e->flag_matrix);
}

char	*find_filename(t_env *e)
{
	t_token	*tokens;

	tokens = start_token(e->tokens);
	while (tokens != NULL) 
	{
		if ((tokens->type == APPEND || tokens->type == TRUNC \
			|| tokens->type == INPUT || tokens->type == HDOC) && \
			last_redir(tokens->next) == 1)
			return (tokens->next->string);
		tokens = tokens->next;
	}
	return (NULL);
}

/* NOTE
** Function that returns 1 if it finds redirection without quotes
*/
int		search_arrows(t_env *e)
{
	t_token	*tokens;
	t_token	*start;

	tokens = start_token(e->tokens);
	while (tokens != NULL)
	{
		start = start_token(tokens);
		tokens = quotes_redirect(e, start);
		if (tokens == NULL)
			return (0);
		else if (tokens->type == APPEND || tokens->type == INPUT || \
		tokens->type == TRUNC || tokens->type == HDOC)
			return (tokens->type);
		tokens = tokens->next;
	}
	return (tokens->type);
}

char	*put_cmd(t_env *e, char *cmd)
{
	int		i;
	int		j;
	char	*str;

	str = (char *)malloc(sizeof(char) * (ft_strlen(e->cmd_path) + cmd_len(cmd) + 1));
	j = 0;
	i = ft_strlen(cmd) - cmd_len(cmd);
	while (cmd[i] != '\0')
	{
		str[j] = cmd[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}
