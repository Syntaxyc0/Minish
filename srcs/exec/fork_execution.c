/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:50:41 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/20 13:24:48 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int dup_io(t_command *cmd)
{
	if (cmd->io < 0)
	{
		if (dup2(cmd->fd[0], STDIN_FILENO) == -1)
			{
				g_exit_status = errno;
				perror(NULL);
				return (-1);
			}
	}
	if (cmd->io == -1 || cmd->io == 2)
	{
		if (dup2(cmd->fd[1], STDOUT_FILENO) == -1)	
		{
			g_exit_status = errno;
			perror(NULL);
			return (-1); 
		}
	}
}

void	execution(t_command *cmd, t_mini *mini)
{
	//dup2 in _ out
	if (dup_io(cmd) == -1)
		return ;
	//close all fd
	if (ft_close_all(cmd) == -1)
		return ;	
}