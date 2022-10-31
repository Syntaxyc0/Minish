/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:55:03 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/29 12:28:18 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_all(t_mini *mini)
{
	t_command	*cmd;
	t_redir		*redir;

	cmd = mini->commands;
	access_in(cmd);
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->type == 4)
				if (redir_in(cmd, redir) == -1)
					return (-1);
			if (redir->type == 5)
				if (ft_heredoc(cmd, redir, mini) == -1)
					return (-1);
			if (redir->type == 6)
				redir_out(cmd, redir);
			if (redir->type == 7)
				ft_append(cmd, redir);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	access_in(t_command *cmd2)
{
	t_command	*cmd;
	t_redir		*redir;

	cmd = cmd2;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->type == 4)
			{
				if (access(redir->filename, R_OK) != 0)
				{
					cmd->io = -3;
					write(2, redir->filename, ft_strlen(redir->filename));
					write(2, ": ", 3);
					return (return_perror(1, 0));
				}
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	redir_in(t_command *cmd, t_redir *redir)
{
	if (cmd->io == -3)
		return (-1);
	if (cmd->fd[0])
	{
		if (close(cmd->fd[0]) == -1)
		{
			g_exit_status = 1;
			perror(NULL);
			return (-1);
		}
	}
	cmd->fd[0] = open(redir->filename, O_RDONLY);
	if (cmd->fd[0] < 0)
	{
		g_exit_status = 1;
		perror(NULL);
		return (-1);
	}
	iocondition_redir_in(cmd);
	return (0);
}

void	redir_out(t_command *cmd, t_redir *redir)
{
	if (cmd->fd[1])
	{
		if (close(cmd->fd[1]) == -1)
		{
			g_exit_status = 1;
			perror(NULL);
			return ;
		}
	}
	cmd->fd[1] = open(redir->filename,
			O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (cmd->fd[1] < 0)
	{
		g_exit_status = 1;
		perror(NULL);
	}
	if (cmd->io != -3)
	{
		if (cmd->io > 0)
			cmd->io = 3;
		else
			cmd->io = -1;
	}
}

void	ft_append(t_command *cmd, t_redir *redir)
{
	if (cmd->fd[1])
	{
		if (close(cmd->fd[1]) == -1)
		{
			g_exit_status = 1;
			perror(NULL);
			return ;
		}
	}
	cmd->fd[1] = open(redir->filename,
			O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (cmd->fd[1] < 0)
	{
		g_exit_status = 1;
		perror(NULL);
	}
	if (cmd->io != -3)
	{
		if (cmd->io > 0)
			cmd->io = 3;
		else
			cmd->io = -1;
	}
}
