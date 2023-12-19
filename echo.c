/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 23:51:33 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/19 13:08:45 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_quotes(t_env *e, t_token *start)
{
	int	i;

	start = start_token(e->tokens);
	e->flag_quotes = 0;
	while (start != NULL)
	{
		i = 0;
		while (start->string[i] != 34 && start->string[i] != 39)
			i++;
		if (check_quotes_closed(start->string, i) == 1)
		{
			if (start->string[i] == 34)
				e->quotes = 2;
			else if (start->string[i] == 39)
				e->quotes = 1;
			break ;
		}
		else
		{
			check_closure(e, start, start->string[i]);
			break ;
		}
		start = start->next;
	}
	quotes_format(e);
}

/* NOTE
** - A number if it founds variable in env
** - -1 if not
*/
int	find_inenv(char **env, char *str)
{
	int	i;
	int	j;
	int	z;

	j = 0;
	i = 0;
	while (str[j] != '$')
		j++;
	if (str[j + 1] == '\0')
		return (0);
	j++;
	while (env[i] != NULL)
	{
		z = 0;
		while (env[i][z] == str[j])
		{
			z++;
			j++;
		}
		if (env[i][z] == '=' && (str[j] == '\0' || str[j] == 34
				|| str[j] == 39))
			return (i);
		i++;
	}
	return (-1);
}

void	echo_expansion(t_env *e)
{
	int	line;
	int	i;
	int	j;

	j = 0;
	while (e->tokens->string[j] != '$')
		j++;
	if (find_inenv(e->env, &e->tokens->string[j]) != -1)
	{
		line = find_inenv(e->env, e->tokens->string);
		i = 0;
		while (e->env[line][i] != '=')
			i++;
		i++;
		printf("%s", &e->env[line][i]);
	}
}

void	last_echo_cmd(t_env *e)
{
	e->quotes = -1;
	if (str_cmp(e->tokens->string, "$?") == 1)
		printf("%d", e->exit_status);
	else if (check_quotes(e->tokens->string) == 1)
		echo_quotes(e, NULL);
	else if (find_dollar(e->tokens->string) == 1 && \
		str_cmp(e->tokens->string, "$") == 0)
		quotes_format(e);
	else
		printf("%s", e->tokens->string);
}

/* NOTE
** - Flag = 1 -> there's -n flag
** - Flag = 0 -> there isn't -n flag
** e->token is already setted to the next token of echo (so if command is
** "echo -n" the token setted is "-n", in case of "echo something" is setted
** on "something")
*/
void	echo_cmd(t_env *e)
{
	t_token	*start;

	while (e->tokens->next != NULL)
	{
		start = start_token(e->tokens);
		if (e->hdoc == 1)
			printf("%s", e->hdoc_str);
		if (check_redir(e) == 1)
			return ;
		e->quotes = -1;
		if (str_cmp(e->tokens->string, "$?") == 1)
			printf("%d", e->exit_status);
		else if (check_quotes(e->tokens->string) == 1)
			echo_quotes(e, NULL);
		else if (find_dollar(e->tokens->string) == 1 && \
			str_cmp(e->tokens->string, "$") == 0)
			quotes_format(e);
		else
			printf("%s", e->tokens->string);
		printf(" ");
		e->tokens = start;
		e->tokens = e->tokens->next;
	}
	last_echo_cmd(e);
}
