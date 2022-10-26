/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_condition.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:02:27 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/26 16:03:30 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_iocondition(t_command *cmd)
{
	if (cmd->io != -3)
	{
		if (cmd->io == -1)
			cmd->io = 3;
		else if (cmd->io == 2 || cmd->io == 1)
			;
		else if (cmd->io == -2)
			cmd->io = 2;
		else
			cmd->io = 1;
	}
}