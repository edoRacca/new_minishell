/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 10:39:27 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/18 19:17:53 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	not_builtin_cmd(char *word)
{
	if (str_cmp(word, "ls") == 1)
		return (1);
	else if (str_cmp(word, "grep") == 1)
		return (1);
	else if (str_cmp(word, "cat") == 1)
		return (1);
	else if (str_cmp(word, "cp") == 1)
		return (1);
	else if (str_cmp(word, "mv") == 1)
		return (1);
	else if (str_cmp(word, "rm") == 1)
		return (1);
	else if (str_cmp(word, "mkdir") == 1)
		return (1);
	else if (str_cmp(word, "clear") == 1)
		return (1);
    else if (str_cmp(word, "wc") == 1)
		return (1);

	else
		return (0);
}

// TODO
int	is_builtin_cmd(char *word)
{
	if (str_cmp(word, "echo") == 1)
		return (1);
	else if (str_cmp(word, "cd") == 1)
		return (1);
	else if (str_cmp(word, "env") == 1)
		return (1);
	else if (str_cmp(word, "export") == 1)
		return (1);
	else if (str_cmp(word, "unset") == 1)
		return (1);
	else if (str_cmp(word, "exit") == 1)
		return (1);
	else if (str_cmp(word, "pwd") == 1)
		return (1);
	else if (str_cmp(word, "history") == 1)
		return (1);
	else 
		return (0);
}

void	select_type(t_token *token, char *word)
{
	if (word[0] == '\0')
		token->type = EMPTY;
	else if (word[0] == 47)
		token->type = PATH;
	else if (is_builtin_cmd(word) == 1)
		token->type = BUILT;
	else if (not_builtin_cmd(word) == 1)
		token->type = NOBUILT;
	else if (word[0] == '-' && ft_isalpha(word[1]) == 1)
		token->type = FLAG;
	else if (str_cmp(word, "|") == 1)
		token->type = PIPE;
	else if (str_cmp(word, ">") == 1)
		token->type = TRUNC;
	else if (str_cmp(word, ">>") == 1)
		token->type = APPEND;
	else if (str_cmp(word, "<") == 1)
		token->type = INPUT;
	else if (str_cmp(word, "<<") == 1)
		token->type = HDOC;
	else
		token->type = ARG;
}

void	parsing(t_env *e)
{
	char **cmd_line;

	cmd_line = ft_split(e->line, ' ');
	if (cmd_line[0] == NULL)
	{
		free_matrix(cmd_line);
		return ;
	}
	else
	{
		init_tokens(e, cmd_line);
		cmd_path(e);
        if (e->cmd_path != NULL && e->tokens->type != PATH && \
        e->tokens->type != NOBUILT)
        {
            free(e->cmd_path);
            e->cmd_path = NULL;
        }
		free_matrix(cmd_line);
	}
}
