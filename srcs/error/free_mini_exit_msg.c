/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mini_exit_msg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:53:22 by ggobert           #+#    #+#             */
/*   Updated: 2022/09/28 15:57:44 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_mini *mini)
{
	t_token	*tmp;
	t_token	*tofree;
	
	tmp = mini->tokens;
	while (tmp != NULL)
	{
		tofree = tmp;
		tmp = tmp->next;
		free(tofree->value);
		free(tofree);
	}
	mini->tokens = NULL;
}

void    free_env(t_mini *mini)
{
	t_env *tmp;
	t_env   *tofree;

	tmp = mini->myenv;
	while (tmp != NULL)
	{
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		tofree = tmp;
		tmp = tmp->next;
		free(tofree);
	}
}

void    free_export(t_mini *mini)
{
	t_export	*tmp;
	t_export	*tofree;

	tmp = mini->myexport;
	while (tmp)
	{
		if (tmp->key)
			free(tmp->key);
		tofree = tmp;
		tmp = tmp->next;
		free(tofree);
	}
}

void	free_redir(t_redir *redir)
{
	t_redir *tmp;
	t_redir *tmp_next;

	tmp = redir;
	while (tmp != NULL)
	{
		if (tmp->filename)
			free(tmp->filename);
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

void    free_mini(t_mini *mini)
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

void	free_mini_exit_msg(t_mini *mini, char *message)
{
	write_error_message(message);
	free_mini(mini);
	exit(g_exit_status);
}
