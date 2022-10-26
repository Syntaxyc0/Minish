/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:55:03 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/26 10:08:42 by ggobert          ###   ########.fr       */
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
				ft_heredoc(cmd, redir);
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

int	redir_in(t_command *cmd, t_redir *redir)
{
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
	if (cmd->io == -1)
		cmd->io = 3;
	else
		cmd->io = 1;
	return (0);
}

int	ft_heredoc(t_command *cmd, t_redir *redir)
{
	char *line;

	if (cmd->fd[0])
	{
		if (close(cmd->fd[0]) == -1)
			return_perror(1, -1);
	}
	redir->heredoc_name = already_exist(redir);
	cmd->fd[0] = open(redir->heredoc_name, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (cmd->fd[0] < 0)
		return_perror(1, 0);
	while (1)
	{
	//signaux!
		line = readline(">");
		if (!ft_strncmp(redir->filename, line, str_big(redir->filename, line)))
			break;
		write(cmd->fd[0], line, ft_strlen(line));
		write(cmd->fd[0], "\n", 1);
	}
	if (cmd->io == -1)
		cmd->io = 3;
	else
		cmd->io = 1;
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
		cmd->fd[1] = 0;
	}
	cmd->fd[1] = open(redir->filename, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (cmd->fd[1] < 0)
	{
		g_exit_status = 1;
		perror(NULL);
	}
	if (cmd->io == 1)
		cmd->io = 3;
	else
		cmd->io = -1;
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
	cmd->fd[1] = open(redir->filename, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (cmd->fd[1] < 0)
	{
		g_exit_status = 1;
		perror(NULL);
	}
	if (cmd->io == 1)
		cmd->io = 3;
	else
		cmd->io = -1;
}
