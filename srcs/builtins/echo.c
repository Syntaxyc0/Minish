/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:44:05 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/22 15:11:56 by ggobert          ###   ########.fr       */
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
	while (cmd->args[i])
	{
		if (i < cmd_args_len(cmd))
		{
			printf("%s", cmd->args[i]);
			if (i != cmd_args_len(cmd) - 1)
				printf(" ");
		}
		i++;
	}
	if (!n_count)
		printf("\n");
}
