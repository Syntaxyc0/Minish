/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:34:16 by gregoiregob       #+#    #+#             */
/*   Updated: 2022/11/02 14:07:01 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_del_unset_env(t_env *tmp, t_env *previous)
{
	if (tmp->key)
		free(tmp->key);
	if (tmp->value)
		free(tmp->value);
	if (previous)
		previous->next = tmp->next;
	free(tmp);
}

void	lst_del_unset_export(t_export *tmp, t_export *previous)
{
	if (tmp->key)
		free(tmp->key);
	if (previous)
		previous->next = tmp->next;
	free(tmp);
}

void	unset_in_env(t_mini *mini, char *args)
{
	t_env	*tmp;
	t_env	*previous;

	previous = 0;
	tmp = mini->myenv;
	printf("args[i] = %s\n", args);
	while (tmp)
	{
		if (ft_strncmp(args, tmp->key, str_big(args, tmp->key)))
		{
			previous = tmp;
			tmp = tmp->next;
		}
		else
		{
			lst_del_unset_env(tmp, previous);
			tmp = previous;
		}
	}
}

void	unset_in_export(t_mini *mini, char *args)
{
	t_export	*tmp;
	t_export	*previous;

	previous = 0;
	tmp = mini->myexport;
	while (tmp)
	{
		if (ft_strncmp(args, tmp->key, str_big(args, tmp->key)) != 0)
		{
			previous = tmp;
			tmp = tmp->next;
		}
		else
		{
			lst_del_unset_export(tmp, previous);
			if (!previous)
				mini->myexport = 0;
			tmp = previous;
		}
	}
}

void	unset(t_mini *mini, t_command *cmd)
{
	int	i;

	g_exit_status = 0;
	i = cmd_args_len(cmd);
	if (i == 1)
		write_error_message(ERR_ARG);
	while (i-- > 1)
	{
		unset_in_env(mini, cmd->args[i]);
		unset_in_export(mini, cmd->args[i]);
	}
}
