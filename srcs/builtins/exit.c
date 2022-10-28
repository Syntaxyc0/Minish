/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:19:01 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/27 12:15:34 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_isdigit(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (isdigit(str[i]) == 0)
			return (0);
	return (1);
}

void	ft_exit(t_command *cmd, t_mini *mini)
{
	if (cmd_args_len(cmd) == 2)
	{
		if (str_isdigit(cmd->args[1]))
			exit(ft_atoi(cmd->args[1]));
		else
		{
			write_error_message("exit : numeric argument required\n");
			g_exit_status = 2;
			free_mini(mini);
			exit(g_exit_status);
		}
	}
	else if (cmd_args_len(cmd) == 1)
	{
		free_mini(mini);
		exit(g_exit_status);
	}
	else
	{
		write_error_message(ERR_ARG);
		return ;
	}
}
