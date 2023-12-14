/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 23:51:17 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/07 12:02:10 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* NOTE
** rewrite the variable value that has closed quotes
** without quotes
*/
char	*rewrite_arg(char *str)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	while (str[i] != '\0')
	{
		if (str[i] != 34 && str[i] != 39)
		{
			tmp[j] = str[i];
			j++;
		}
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}

/* NOTE
** check if the var exported exists or not in env matrix
** 1 exists and it's equal to str - 2 exists but it's different - 0 no match
*/
int	exp_var_exists(t_env *e, char *str)
{
	int	i;

	i = 0;
	while (e->env[i] != NULL)
	{
		if (str_cmp(e->env[i], str) == 1)
			return (1);
		if (exp_var_name(e->env[i], str) != -1)
			return (2);
		i++;
	}
	return (0);
}

/* NOTE
** 1 variable exported exists in env and it's equal to the other
** 2 variable exported exists but has different value
** 0 (else) variable doesn't exists
*/
void	export_var(t_env *e, char *str, int flag)
{
	char	**tmp_e;
	int		i;

	i = 0;
	if (flag == 1)
		return ;
	else if (flag == 2)
		over_exp_var(e, str);
	else
	{
		tmp_e = (char **)malloc(sizeof(char *) * (size_env(e->env) + 1));
		tmp_e = copy_env_temp(e->env, tmp_e, str);
		free_matrix(e->env);
		e->env = (char **)malloc(sizeof(char *) * size_env(tmp_e));
		while (tmp_e[i] != NULL)
		{
			e->env[i] = (char *)malloc(sizeof(char) * ft_strlen(tmp_e[i]) + 1);
			copy_line(e->env[i], tmp_e[i]);
			i++;
		}
		e->env[i] = NULL;
		free_matrix(tmp_e);
	}
	e->exit_status = 0;
}

/* NOTE
** check:
** - if var has quotes: if it has check if quotes are closed or not
**  - if are closed they must not be written in the env
**  - if are not closed they must be printed normally (quotes
**    must not be handled)
** - if var hasn't quotes must be printed in env
** After this starts the export of the varyable to export
*/
void	parsing_exp_var(t_env *e)
{
	char	*tmp;
	int		i;
	int		flag;

	i = 0;
	while (e->tokens->string[i] != '=')
		i++;
	i++;
	if (check_quotes(&e->tokens->string[i]) == 1)
	{
		while (e->tokens->string[i] != 34 && e->tokens->string[i] != 39)
			i++;
		if (check_quotes_closed(e->tokens->string, i) == 1)
		{
			tmp = rewrite_arg(e->tokens->string);
			flag = exp_var_exists(e, tmp);
			export_var(e, tmp, flag);
			free(tmp);
			return ;
		}
	}
	flag = exp_var_exists(e, e->tokens->string);
	export_var(e, e->tokens->string, flag);
}

/* NOTE
** check:
** - if var name is alphanumerical excluding the first character
** that must be only alphabetical
** - if there's a equal symbol in the argument to export
** After this starts the parsing of the varyable to export
*/
void	export_function(t_env *e)
{
	if (is_all_alpha(e->tokens->string) == 1)
	{
		e->tokens = e->tokens->prev;
		invalid_identif(e);
		return ;
	}
	else if (check_equal(e->tokens->string) == 0)
	{
		e->exit = 1;
		e->exit_status = 0;
		return ;
	}
	parsing_exp_var(e);
}
