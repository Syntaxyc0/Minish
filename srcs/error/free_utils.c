/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:58:23 by jbesnier          #+#    #+#             */
/*   Updated: 2022/10/26 15:55:36 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir(t_redir *redir)
{
	t_redir	*tmp;
	t_redir	*tmp_next;

	tmp = redir;
	while (tmp != NULL)
	{
		if (tmp->filename)
			free(tmp->filename);
		if (tmp->heredoc_name)
			free(tmp->heredoc_name);
		tmp_next = tmp->next;
		free(tmp);
		tmp = tmp_next;
	}
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_commands(t_mini *mini)
{
	t_command	*cmd;
	t_command	*tmp;

	cmd = mini->commands;
	while (cmd != NULL)
	{
		if (cmd->fullpath)
			free(cmd->fullpath);
		if (cmd->redir)
		{
			free_redir(cmd->redir);
			cmd->redir = NULL;
		}
		if (cmd->args)
		{
			free_array(cmd->args);
			cmd->args = NULL;
		}
		tmp = cmd->next;
		free(cmd);
		cmd = tmp;
	}
	mini->commands = NULL;
}

void	free_mini(t_mini *mini)
{
	int	i;

	i = -1;
	if (mini->myenv)
		free_env(mini);
	if (mini->myexport)
		free_export(mini);
	if (mini->tokens)
		free_tokens(mini);
	if (mini->all_path)
	{
		while (mini->all_path[++i])
			free(mini->all_path[i]);
		free(mini->all_path);
	}
	if (mini->commands)
		free_commands(mini);
	free(mini);
}
