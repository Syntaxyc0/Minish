/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 13:11:23 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/20 13:14:51 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_close_all(t_mini *mini)
{
	t_command *cmd;

	cmd = mini->commands;
	while (cmd)	
	{
		if (close(cmd->fd[0]) == -1)
		{
			g_exit_status = errno;
			perror(NULL);
		}
		if (close(cmd->fd[1]) == -1)
		{
			g_exit_status = errno;
			perror(NULL);
		}
		
	}
}