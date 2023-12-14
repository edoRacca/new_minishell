/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 12:24:53 by eraccane          #+#    #+#             */
/*   Updated: 2023/11/24 12:36:12 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	invalid_identif(t_env *e)
{
	e->exit = 1;
	e->exit_status = 1;
	printf("minishell: %s: '%s': not a valid identifier\n", e->tokens->string, \
		e->tokens->next->string);
}