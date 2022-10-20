/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:50:41 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/20 14:05:49 by ggobert          ###   ########.fr       */
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

void	execution(t_command *cmd, t_mini *mini)
{
	//dup2 in _ out
	if (dup_io(cmd) == -1)
		return ;
	//close all fd
	if (ft_close_all(mini) == -1)
		return ;
	//access
	if (ft_access(mini) == -1)
		return ;
	//execve	
}