/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 10:39:27 by eraccane          #+#    #+#             */
/*   Updated: 2023/11/21 23:01:59 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	not_builtin_cmd(char *word)
{
	if (str_compare(word, "ls") == 1)
		return (1);
	else if (str_compare(word, "grep") == 1)
		return (1);
	else if (str_compare(word, "cat") == 1)
		return (1);
	else if (str_compare(word, "cp") == 1)
		return (1);
	else if (str_compare(word, "mv") == 1)
		return (1);
	else if (str_compare(word, "rm") == 1)
		return (1);
	else if (str_compare(word, "mkdir") == 1)
		return (1);
	else
		return (0);
}

// TODO
int	is_builtin_cmd(char *word)
{
	if (str_compare(word, "echo") == 1)
		return (1);
	else if (str_compare(word, "cd") == 1)
		return (1);
	else if (str_compare(word, "env") == 1)
		return (1);
	else if (str_compare(word, "export") == 1)
		return (1);
	else if (str_compare(word, "unset") == 1)
		return (1);
	else if (str_compare(word, "exit") == 1)
		return (1);
	else if (str_compare(word, "pwd") == 1)
		return (1);
	else if (str_compare(word, "history") == 1)
		return (1);
	else 
		return (0);
}

void	select_token_type(t_token *token, char *word)
{
	if (word == NULL)
		token->token_type = TK_EMPTY;
	else if (word[0] == 47)
		token->token_type = TK_PATH;
	else if (is_builtin_cmd(word) == 1)
		token->token_type = TK_CMD_BUILT;
	else if (not_builtin_cmd(word) == 1)
		token->token_type = TK_CMD_NOBUILT;
	else if (word[0] == '-' && ft_isalpha(word[1]) == 1)
		token->token_type = TK_FLAG;
	else if (word[0] == '|')
		token->token_type = TK_PIPE;
	else if (word[0] == '>')
	{
		if (word[1] == '>')
			token->token_type = TK_APPEND;
		else
			token->token_type = TK_TRUNC;
	}
	else if (word[0] == '<')
		token->token_type = TK_INPUT;
	else
		token->token_type = TK_ARG;
}

void	parsing(t_env *e)
{
	char **cmd_line;

	cmd_line = ft_split(e->line, ' ');
	init_tokens(e, cmd_line);
	// print_matrix(cmd_line);
	print_tokens(e->tokens);
	free_matrix(cmd_line);
}