/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:25:17 by ggobert           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/10/25 14:15:20 by ggobert          ###   ########.fr       */
=======
/*   Updated: 2022/10/26 10:22:17 by ggobert          ###   ########.fr       */
>>>>>>> greg
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
		{
			g_exit_status = errno;
			perror(NULL);
			return (-1);
		}
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
		if (is_builtin(cmd->args[0]) && cmd_len(mini) == 1)
			builtin_process(cmd, mini);
		else if (cmd->args[0])
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
			wait(&g_exit_status);
		cmd = cmd->next;
	}
	g_exit_status = g_exit_status / 256;
	heredoc_anihilator(mini);
	return (0);
}
