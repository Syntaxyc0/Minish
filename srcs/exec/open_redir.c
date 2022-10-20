/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:55:03 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/20 13:11:09 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_all(t_mini *mini)
{
	t_command	*cmd;
	
	cmd = mini->commands;
	while (cmd)
	{
		while (cmd->redir)
		{
			if (cmd->redir->type == 4)
				if (redir_in(cmd) == -1);
					return (-1);
			if (cmd->redir->type == 5)
				ft_heredoc(cmd);
			if (cmd->redir->type == 6)
				redir_out(cmd);
			if (cmd->redir->type == 7)
				ft_append(cmd);
			cmd->redir = cmd->redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	redir_in(t_command *cmd)
{
	cmd->fd[0] = open(cmd->redir->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644)
	if (cmd->fd[0] < 0)
	{
		g_exit_status = errno;
		perror(NULL);
		return (-1);
	}
	if (cmd->io == -1)
		cmd->io = 2;
	else
		cmd->io = 1;
	return (0);
}

int	ft_heredoc(t_command *cmd)
{	
}

void	redir_out(t_command *cmd)
{
	cmd->fd[1] = open(cmd->redir->filename, O_RDONLY)
	if (cmd->fd[1] < 0)
	{
		g_exit_status = errno;
		perror(NULL);
	}
	if (cmd->io == 1)
		cmd->io = 2;
	else
		cmd->io = -1;
}

void	ft_append(t_command *cmd)
{
	cmd->fd[0] = open(cmd->redir->filename, O_CREAT | O_WRONLY | O_APPEND, 0644)
	if (cmd->fd[0] < 0)
	{
		g_exit_status = errno;
		perror(NULL);
	}
	if (cmd->io == 1)
		cmd->io = 2;
	else
		cmd->io = -1;
}