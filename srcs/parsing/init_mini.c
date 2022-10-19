/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbesnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:55:18 by jbesnier          #+#    #+#             */
/*   Updated: 2022/09/27 16:55:21 by jbesnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini	*init_mini(void)
{
	t_mini	*mini;

	mini = malloc(sizeof(t_mini));
	if (!mini)
	{
		write_error_message(ERR_MALLOC);
		exit (1);
	}
	mini->myenv = NULL;
	mini->myexport = NULL;
	mini->tokens = NULL;
	mini->commands = NULL;
	return (mini);
}
