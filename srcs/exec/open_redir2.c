/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redir2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:21:50 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/26 11:33:06 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char	*already_exist(t_redir *redir)
{
	char	*ret;
	
	ret = ft_strdup(redir->filename);
	while (access(ret, R_OK) == 0)
	{
		ret = ft_strjoin_free(ret, "0", 1, 0);
	}
	return (ret);
}

void	heredoc_anihilator(t_mini *mini)
{
	t_command	*cmd;
	t_redir		*redir;

	cmd = mini->commands;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (cmd->redir->type == 5)
				if (unlink(redir->heredoc_name) == -1)
					return_perror(1, 0);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

void	access_in(t_command *cmd2)
{
	t_command	*cmd;
	t_redir		*redir;

	cmd = cmd2;
	while (cmd)
	{
		redir = cmd->redir;
		while (redir)
		{
			if (redir->type == 4)
			{
				if (access(redir->filename, R_OK) != 0)
				{
					cmd->io = -3;
					return_perror(1, 0);
				}
			}
			redir = redir->next;
		}
		cmd =cmd->next;
	}
}