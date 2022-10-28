/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:50:41 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/28 12:06:52 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup_io(t_command *cmd)
{
	if (cmd->io > 0)
		if (dup2(cmd->fd[0], STDIN_FILENO) == -1)
			return (return_perror(1, -1));
	if (cmd->io == -1 || cmd->io == 3)
		if (dup2(cmd->fd[1], STDOUT_FILENO) == -1)
			return (return_perror(1, -1));
	if (cmd->io == 2 || cmd->io == -2)
		if (dup2(cmd->next->fd[1], STDOUT_FILENO) == -1)
			return (return_perror(1, -1));
	return (0);
}

int	ft_close_all(t_mini *mini)
{
	t_command	*cmd;

	cmd = mini->commands;
	while (cmd)
	{
		if (cmd->fd[0])
		{
			if (close(cmd->fd[0]) == -1)
				return_perror(1, 0);
			cmd->fd[0] = 0;
		}
		if (cmd->fd[1])
		{
			if (close(cmd->fd[1]) == -1)
				return_perror(1, 0);
			cmd->fd[1] = 0;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	check_relative(t_mini *mini, t_command *cmd)
{
	int		i;
	char	*tmp;
	char	*path;

	i = -1;
	while (mini->all_path[++i])
	{
		tmp = ft_strjoin(mini->all_path[i], "/");
		if (!tmp)
			exit_free_status_msg(mini, 1, ERR_MALLOC);
		path = ft_strjoin_free(tmp, cmd->args[0], 1, 0);
		if (!path)
			exit_free_status_msg(mini, 1, ERR_MALLOC);
		if (access(path, X_OK) == 0)
		{
			cmd->fullpath = path;
			return (1);
		}
		free(path);
	}
	return (0);
}

int	ft_access(t_command *cmd, t_mini *mini)
{
	int	relative;

	relative = check_relative(mini, cmd);
	if (relative)
		return (0);
	if (access(cmd->args[0], X_OK) == 0)
	{
		cmd->fullpath = cmd->args[0];
		return (0);
	}
	error_args(cmd->args[0], ": command not found\n", 127);
	return (-1);
}

void	execution(t_command *cmd, t_mini *mini)
{
	if (!is_builtin(cmd->args[0]))
	{
		if (dup_io(cmd) == -1)
			exit_free_status(mini, g_exit_status);
		if (ft_close_all(mini) == -1)
			exit_free_status(mini, g_exit_status);
		if (ft_access(cmd, mini) == -1)
			exit_free_status(mini, g_exit_status);
		if (execve(cmd->fullpath, cmd->args, mini->environment) == -1)
			exit_perror(g_exit_status);
	}
	else
		builtin_process(cmd, mini);
	exit_free_status(mini, g_exit_status);
}
