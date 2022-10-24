/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:44:05 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/24 10:29:33 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_command *cmd)
{
	int	i;
	int	n_count;

	i = 1;
	n_count = 0;
	if (cmd_args_len(cmd) == 1)
		return ;
	while (!ft_strncmp(cmd->args[i], "-n", str_big(cmd->args[i], "-n")))
	{
		n_count++;
		i++;
	}
	echo_print_args(cmd, i);
	if (!n_count)
	{
		if (any_redir_out(cmd))
			write(cmd->fd[1], "\n", 1);
		else
			printf("\n");
	}
}

void	echo_print_args(t_command *cmd, int i)
{
	while (cmd->args[i])
	{
		if (i < cmd_args_len(cmd))
		{
			if (any_redir_out(cmd))
			{
				write(cmd->fd[1], cmd->args[i], ft_strlen(cmd->args[i]));
				if (i != cmd_args_len(cmd) - 1)
					write(cmd->fd[1], " ", 1);
			}
			else
			{
				printf("%s", cmd->args[i]);
				if (i != cmd_args_len(cmd) - 1)
					printf(" ");
			}
		}
		i++;
	}
}