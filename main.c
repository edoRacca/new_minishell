/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 18:14:15 by eraccane          #+#    #+#             */
/*   Updated: 2023/11/21 22:43:35 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int	main(int ac, char *av[], char **env)
{
	t_env	*e;

	(void)ac;
	(void)av;
	// (void)env;
	e = malloc(sizeof(t_env));
	init_env(e, env);
	while(1)
	{
		signals(e);
		e->line = readline("$> ");
		if (e->line == NULL)
			ctrl_d(e);
		parsing(e);
		if (e->line[0] != '\0')
			add_history(e->line);
		// printf("|%s|\n", e->line);
		free_tokens(&e->tokens);
	}
}
