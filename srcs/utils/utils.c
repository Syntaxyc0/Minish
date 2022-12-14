/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:26:11 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/29 11:03:38 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_big(char *a, char *b)
{
	if (ft_strlen(a) > ft_strlen(b))
		return (ft_strlen(a));
	else
		return (ft_strlen(b));
}

void	get_all_path(t_mini *mini)
{
	int		i;
	t_env	*ev;

	i = -1;
	ev = mini->myenv;
	while (ev && ft_strncmp(ev->key, "PATH", str_big(ev->key, "PATH")))
		ev = ev->next;
	if (mini->all_path)
	{
		while (mini->all_path[++i])
			free(mini->all_path[i]);
		free(mini->all_path);
		mini->all_path = NULL;
	}
	if (!ev)
		return ;
	mini->all_path = ft_split(ev->value, ':');
}

int	cmd_len(t_mini *mini)
{
	int			i;
	t_command	*cmd;

	i = 0;
	cmd = mini->commands;
	while (cmd)
	{
		i++;
		cmd = cmd->next;
	}
	return (i);
}

int	cmd_args_len(t_command *cmd)
{
	int			i;

	i = 0;
	while (cmd->args[i])
		i++;
	return (i);
}

int	any_redir_out(t_command *cmd)
{
	t_redir	*redir;

	redir = cmd->redir;
	while (redir)
	{
		if (redir->type == 6 || redir->type == 7)
			return (1);
		redir = redir->next;
	}
	return (0);
}
