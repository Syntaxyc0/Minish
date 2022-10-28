/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:25:17 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/28 14:40:24 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	io_cmd(t_mini *mini)
{
	int			i;
	t_command	*cmd;

	i = 2;
	cmd = mini->commands;
	if (cmd_len(mini) == 1)
		cmd->io = 0;
	else
		cmd->io = -2;
	cmd = cmd->next;
	while (cmd)
	{
		if (i == cmd_len(mini))
			cmd->io = 1;
		else
			cmd->io = 2;
		cmd = cmd->next;
		i++;
	}
}

int	init_pipe(t_mini *mini)
{
	t_command	*cmd;

	cmd = mini->commands;
	while (cmd)
	{
		if (pipe(cmd->fd) == -1)
			return_perror(1, -1);
		cmd = cmd->next;
	}
	return (0);
}

int	processes(t_mini *mini)
{
	t_command	*cmd;

	cmd = mini->commands;
	while (cmd)
	{
		if (is_builtin(cmd->args[0]) && cmd_len(mini) == 1 && cmd->io != -3)
			builtin_process(cmd, mini);
		else if (cmd->args[0] && cmd->io != -3)
		{
			cmd->pid = fork();
			if (cmd->pid == -1)
			{
				perror(NULL);
				return (-1);
			}
			if (cmd->pid == 0)
				execution(cmd, mini);
		}
		cmd = cmd->next;
	}
	return (0);
}

int	exec(t_mini *mini)
{
	t_command	*cmd;

	cmd = mini->commands;
	io_cmd(mini);
	get_all_path(mini);
	if (init_pipe(mini) == -1)
		return (-1);
	if (ft_open_all(mini) == -1)
		return (0);
	if (processes(mini) == -1)
		return (-1);
	ft_close_all(mini);
	process_sig_handle();
	while (cmd)
	{
		if (!is_builtin(cmd->args[0]) || cmd_len(mini) > 1)
			waitpid(cmd->pid, &g_exit_status, 0);
		cmd = cmd->next;
	}
	heredoc_annihilator(mini);
	g_exit_status /= 256;
	return (0);
}
