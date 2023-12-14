/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 09:40:25 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/09 22:13:23 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* NOTE
** print function for echo command. It prints a string from a start index
*/
void	echo_print_str(char *str, int start)
{
	if (str == NULL)
		return ;
	while (str[start] != '\0')
	{
		printf("%c", str[start]);
		start++;
	}
}

/* NOTE
** check if the nobuilt command is empty
** - 1 if it's not empty
** - 0 if it's empty
*/
int	empty_cmd(t_env *e)
{
	int	i;

	i = 0;
	while (e->tokens->string[i] != '\0')
	{
		if (e->tokens->string[i] != ' ' && e->tokens->string[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

int	count_flag(t_env *e)
{
	t_token	*tokens;
	int		i;

	i = 0;
	tokens = start_token(e->tokens);
	while (tokens != NULL && tokens->type != PIPE && tokens->type != INPUT && \
			tokens->type != APPEND && tokens->type != TRUNC)
	{
		i++;
		tokens = tokens->next;
	}
	return (i);
}

void	print_argtype(t_env *e)
{
	t_token	*tokens;

	tokens = start_token(e->tokens);
	while (tokens != NULL)
	{
		printf("token type: %d\n", tokens->type);
		tokens = tokens->next;
	}
}

/* NOTE
** It finds out command lenght to do malloc of first matrix flag string 
*/
int	cmd_len(char *str)
{
	int	i;
	int	len;

	i = ft_strlen(str) - 1;
	while (str[i] != 47 && i != 0)
		i--;
	if (i != 0)
		i++;
	len = 0;
	while (str[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}
