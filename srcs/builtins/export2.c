/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 11:47:32 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/27 15:27:39 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_egal(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == '=')
			return (1);
	return (0);
}

int	is_space_before_egal(char *s)
{
	int	i;

	i = -1;
	while (s[++i] && s[i] != '=')
		if (s[i] == ' ')
			return (1);
	return (0);
}

void	init_myexport(t_mini *mini, char *s)
{
	mini->myexport = malloc(sizeof(t_export));
	if (!mini->myexport)
		free_mini_exit_msg(mini, ERR_MALLOC);
	mini->myexport->key = ft_strdup(s);
	mini->myexport->next = 0;
	if (!mini->myexport->key)
		free_mini_exit_msg(mini, ERR_MALLOC);
}


int	already_in_env(t_mini *mini, char *key, char *value)
{
	t_env	*env;
	
	env = mini->myenv;
	while (env)
	{
		if (!ft_strncmp(key, env->key, str_big(key, env->key)))
		{
			free(env->value);
			env->value = ft_strdup(value);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	already_in_export(t_mini *mini, char *key)
{
	t_export	*export;

	export = mini->myexport;
	while (export)
	{
		if (!ft_strncmp(key, export->key, str_big(key, export->key)))
			return (1);
		export = export->next;
	}
	return (0);
}