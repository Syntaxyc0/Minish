/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:44:05 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/29 12:39:13 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_command *cmd, t_mini *mini)
{
	int	i;
	int	n_count;

	n_count = 0;
	if (cmd_args_len(cmd) == 1)
<<<<<<< HEAD
	{
		printf("\n");
		return ;
	}
	while (!ft_strncmp(cmd->args[i], "-n", str_big(cmd->args[i], "-n")))
=======
>>>>>>> d305d9c61b0f8f7dcf59bba3bcbbfb8fbdce0473
	{
		echo_nl(cmd, mini);
		return ;
	}
	i = echo_n_manager(cmd);
	if (i > 1)
		n_count++;
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

void	echo_nl(t_command *cmd, t_mini *mini)
{
	if (any_redir_out(cmd) && cmd_len(mini) == 1)
		write(cmd->fd[1], "\n", 1);
	else
		printf("\n");
}

int	echo_n_manager(t_command *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd->args[++i])
	{
		j = 0;
		if (cmd->args[i][j++] == '-')
		{
			while (cmd->args[i][j] == 'n' && cmd->args[i][j])
				j++;
			if (cmd->args[i][j])
				return (i);
		}
		else
			return (i);
	}
	return (i);
}
