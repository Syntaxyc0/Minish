/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:34:15 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/29 12:39:48 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_process(t_command *cmd, t_mini *mini)
{
	if (cmd_len(mini) > 1)
		if (dup_io(cmd) == -1)
			exit_free_status(mini, g_exit_status);
	which_builtin(cmd, mini);
	if (ft_close_all(mini) == -1)
		exit_free_status(mini, g_exit_status);
}

void	which_builtin(t_command *cmd, t_mini *mini)
{
	if (!ft_strncmp(cmd->args[0], "echo", str_big(cmd->args[0], "echo")))
	{
		echo(cmd, mini);
		return ;
	}
	if (!ft_strncmp(cmd->args[0], "cd", str_big(cmd->args[0], "cd")))
	{
		cd(cmd, mini);
		return ;
	}
	if (!ft_strncmp(cmd->args[0], "pwd", str_big(cmd->args[0], "pwd")))
	{
		pwd(cmd, mini);
		return ;
	}
	if (!ft_strncmp(cmd->args[0], "export", str_big(cmd->args[0], "export")))
	{
		export(mini, cmd);
		return ;
	}
	which_builtin2(cmd, mini);
}

void	which_builtin2(t_command *cmd, t_mini *mini)
{
	if (!ft_strncmp(cmd->args[0], "unset", str_big(cmd->args[0], "unset")))
	{
		unset(mini, cmd);
		return ;
	}
	if (!ft_strncmp(cmd->args[0], "env", str_big(cmd->args[0], "env")))
	{
		env(mini, cmd);
		return ;
	}
	if (!ft_strncmp(cmd->args[0], "exit", str_big(cmd->args[0], "exit")))
		ft_exit(cmd, mini);
}
