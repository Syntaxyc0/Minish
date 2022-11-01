/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:58:10 by ggobert           #+#    #+#             */
/*   Updated: 2022/11/01 11:58:25 by ggobert          ###   ########.fr       */
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
