/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:44:05 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/26 10:28:10 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_command *cmd, t_mini *mini)
{
	int	i;
	int	n_count;

	i = 1;
	n_count = 0;
	if (cmd_args_len(cmd) == 1)
	{
		printf("\n");
		return ;
	}
	while (!ft_strncmp(cmd->args[i], "-n", str_big(cmd->args[i], "-n")))
	{
		n_count++;
		i++;
	}
	echo_print_args(cmd, mini, i);
	if (!n_count)
	{
		if (any_redir_out(cmd) && cmd_len(mini) == 1)
			write(cmd->fd[1], "\n", 1);
		else
			printf("\n");
	}
}

void	echo_print_args(t_command *cmd, t_mini *mini, int i)
{
	while (cmd->args[i])
	{
		if (i < cmd_args_len(cmd))
		{
			if (any_redir_out(cmd) && cmd_len(mini) == 1)
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
