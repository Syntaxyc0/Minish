/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 15:19:01 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/21 16:18:37 by ggobert          ###   ########.fr       */
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

void	ft_exit(t_command *cmd)
{
	if (cmd_args_len(cmd) == 2)
	{
		if (str_isdigit(cmd->args[1]))
			exit(ft_atoi(cmd->args[1]));
		else
		{
			write_error_message("msh : numeric argument required");
			exit(g_exit_status);
		}
	}
	else if (cmd_args_len(cmd) == 1)
		exit(g_exit_status);
	else
	{
		write_error_message(ERR_ARG);
		return ;
	}
}
