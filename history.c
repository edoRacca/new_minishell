/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:43:16 by eraccane          #+#    #+#             */
/*   Updated: 2023/11/17 19:27:21 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_history(t_env *e)
{
	int	i;

	e->history = history_list();
	i = 0;
	if (e->history != NULL)
	{
		while (e->history[i] != NULL)
		{
			printf(" %d  %s\n", i + 1, e->history[i]->line);
			i++;
		}
	}
	else
	{
		printf("history is empty\n");
	}
}