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

void	free_env(t_mini *mini)
{
	t_env	*tmp;
	t_env	*tofree;

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

void	free_export(t_mini *mini)
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

void	free_mini_exit_msg(t_mini *mini, char *message)
{
	write_error_message(message);
	free_mini(mini);
	exit(g_exit_status);
}

void	exit_free_status_msg(t_mini *mini, int ges, char *msg)
{
	g_exit_status = ges;
	write_error_message(msg);
	free_mini(mini);
	exit(g_exit_status);
}

void	exit_free_status(t_mini *mini, int ges)
{
	g_exit_status = ges;
	free_mini(mini);
	exit(g_exit_status);
}
