/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:43:16 by eraccane          #+#    #+#             */
/*   Updated: 2023/11/23 17:44:53 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_history(void)
{
	int	i;
	HIST_ENTRY	**history;

	history = history_list();
	i = 0;
	if (history != NULL)
	{
		while (history[i] != NULL)
		{
			printf(" %d  %s\n", i + 1, history[i]->line);
			i++;
		}
	}
	else
	{
		printf("history is empty\n");
	}
}
