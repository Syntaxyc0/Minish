/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:35:25 by ggobert           #+#    #+#             */
/*   Updated: 2022/11/01 11:37:11 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env(t_mini *mini, t_command *cmd)
{
	t_env	*tmp;

	g_exit_status = 0;
	tmp = mini->myenv;
	while (tmp)
	{
		if (any_redir_out(cmd))
		{
			write(cmd->fd[1], tmp->key, ft_strlen(tmp->key));
			write(cmd->fd[1], "=", 1);
			if (tmp->value)
				write(cmd->fd[1], tmp->value, ft_strlen(tmp->value));
			write(cmd->fd[1], "\n", 1);
		}
		else
		{
			printf("%s=", tmp->key);
			if (tmp->value)
				printf("%s", tmp->value);
			printf("\n");
		}
		tmp = tmp->next;
	}	
}
