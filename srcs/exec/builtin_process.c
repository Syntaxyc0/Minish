/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:34:15 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/21 16:33:24 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_process(t_command *cmd, t_mini *mini)
{
	if (!ft_strncmp(cmd->args[0], "echo", str_big(cmd->args[0], "echo")))
		return ;
	if (!ft_strncmp(cmd->args[0], "cd", str_big(cmd->args[0], "cd")))
	{
		cd(cmd, mini);
		return ;
	}
	if (!ft_strncmp(cmd->args[0], "pwd", str_big(cmd->args[0], "pwd")))
		return ;
	if (!ft_strncmp(cmd->args[0], "export", str_big(cmd->args[0], "export")))
		return ;
	if (!ft_strncmp(cmd->args[0], "unset", str_big(cmd->args[0], "unset")))
		return ;
	if (!ft_strncmp(cmd->args[0], "env", str_big(cmd->args[0], "env")))
		return ;
	if (!ft_strncmp(cmd->args[0], "exit", str_big(cmd->args[0], "exit")))
		ft_exit(cmd);
}