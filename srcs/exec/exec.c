/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 13:25:17 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/20 17:05:05 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_pipe(t_mini *mini)
{
	t_command	*cmd;

	cmd = mini->commands;
	while (cmd)
	{
		if (pipe(cmd->fd) == -1)
			{
				g_exit_status = errno;
				perror(NULL);
				return (-1);
			}
		cmd = cmd->next;
	}
}

int	processes(t_mini *mini)
{
	t_command	*cmd;

	cmd = mini->commands;
	while (cmd)
	{
		cmd->pid = fork();
		if (cmd->pid == -1)
			{
				g_exit_status = errno;
				perror(NULL);
				return (-1);
			}
		if (cmd->pid == 0)
			execution(cmd, mini);
	}
	return (0);
}

int	exec(t_mini *mini)
{
	int			i;
	t_command	*cmd;

	i = -1;
	cmd = mini->commands;
	//les path -> char ** (optionnel, may init ailleur)
	get_all_path(mini);
	//pipe init (REMPLIR fd par les pipes) ___(KILL EXEC si err) (WARNING une seule execution non géré)
	if (init_pipe(mini) == -1)
		return (-1);
	//ft_open_all(REMPLACER les fd par les redir) ____(KILL EXEC si err SEULEMENT sur fd in)
	if (ft_open_all(mini)== -1)
		return (-1);
	//fork
		//process ____(KILL EXEC si err)
	if (processes(mini) == -1)
		return (-1);
	while (++i < cmd_len(mini))
		wait(NULL);
	//close
	ft_close_all(mini);
	return (0);
}