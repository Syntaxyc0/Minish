/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:34:16 by gregoiregob       #+#    #+#             */
/*   Updated: 2022/10/22 12:49:42 by ggobert          ###   ########.fr       */
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


void	unset_in_env(t_mini *mini, char **args)
{
	int		i;
	t_env	*tmp;
	t_env	*previous;

	i = 1;
	previous = 0;
	tmp = mini->myenv;
	while (tmp)
	{
		if (ft_strncmp(args[i], tmp->key, str_big(args[i], tmp->key)) != 0)
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
	i++;
}

void	unset_in_export(t_mini *mini, char **args)
{
	int			i;
	t_export	*tmp;
	t_export	*previous;

	i = 1;
	previous = 0;
	tmp = mini->myexport;
	while (tmp)
	{
		if (ft_strncmp(args[i], tmp->key, str_big(args[i], tmp->key)) != 0)
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
	i++;
}

void	unset(t_mini *mini, t_command *cmd)
{
	int	i;
	i = cmd_args_len(cmd);
	if (i == 1)
		write_error_message(ERR_ARG);
	while (i-- > 1)
	{
		if (check_args(cmd_args_len(cmd), cmd->args) != 0)
			return ;
		unset_in_env(mini, cmd->args);
		unset_in_export(mini, cmd->args);
	}
}
