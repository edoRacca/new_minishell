/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 18:14:15 by eraccane          #+#    #+#             */
/*   Updated: 2023/11/12 22:51:55 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(int ac, char *av[], char **env)
{
	t_env	*e;

	(void)ac;
	(void)av;
	e = malloc(sizeof(t_env));
	init_env(e, env);
	while(1)
	{
		e->line = readline("$>" );
		// printf("%s\n", e->line);
	}
}
