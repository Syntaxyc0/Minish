/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:19:01 by ggobert           #+#    #+#             */
/*   Updated: 2022/11/09 12:09:57 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_isdigit(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '-')
		i++;
	while (str[++i])
		if (isdigit(str[i]) == 0)
			return (0);
	return (1);
}

void	ft_exit(t_command *cmd, t_mini *mini)
{
	if (cmd_args_len(cmd) == 2)
		exit_one_args(cmd, mini);
	else if (cmd_args_len(cmd) == 1)
		exit_no_arg(mini);
	else
	{
		if (!str_isdigit(cmd->args[1]))
		{
			write_error_message("exit\n");
			write_error_message("msh : exit : numeric argument required\n");
			g_exit_status = 2;
			free_mini(mini);
			exit(g_exit_status);
		}
		else
		{
			write_error_message("exit\n");
			write_error_message("msh : exit : ");
			write_error_message(ERR_ARG);
		}
		return ;
	}
}

void	exit_one_args(t_command *cmd, t_mini *mini)
{
	if (str_isdigit(cmd->args[1]))
	{
		write_error_message("exit\n");
		exit(ft_atoi(cmd->args[1]));
	}
	else
	{
		write_error_message("exit\n");
		write_error_message("msh : exit : numeric argument required\n");
		g_exit_status = 2;
		free_mini(mini);
		exit(g_exit_status);
	}
}

void	exit_no_arg(t_mini *mini)
{
	write_error_message("exit\n");
	free_mini(mini);
	exit(g_exit_status);
}
