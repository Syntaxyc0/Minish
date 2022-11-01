/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregoiregobert <gregoiregobert@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:52:13 by gregoiregob       #+#    #+#             */
/*   Updated: 2022/09/22 15:52:13 by gregoiregob      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_myenv(t_mini *mini, char *key, char *value)
{
	mini->myenv = malloc(sizeof(t_env));
	if (!mini->myenv)
		free_mini_exit_msg(mini, ERR_MALLOC);
	mini->myenv->key = ft_strdup(key);
	mini->myenv->value = ft_strdup(value);
	mini->myenv->next = NULL;
	if (!mini->myenv->key || !mini->myenv->value)
		free_mini_exit_msg(mini, ERR_MALLOC);
}

void	free_envelem_key_value(t_env *ret, char *key, char *value)
{
	if (ret->key)
		free(ret->key);
	if (key)
		free(key);
	if (value)
		free(value);
	free(ret);
}

t_env	*init_envelem(t_mini *mini, char *key, char *value)
{
	t_env	*ret;

	ret = malloc(sizeof(t_env));
	if (!ret)
		free_mini_exit_msg(mini, ERR_MALLOC);
	ret->key = ft_strdup(key);
	if (!ret->key)
	{
		free_envelem_key_value(ret, key, value);
		free_mini_exit_msg(mini, ERR_MALLOC);
	}
	if (value)
	{
		ret->value = ft_strdup(value);
		if (!ret->value)
		{
			free_envelem_key_value(ret, key, value);
			free_mini_exit_msg(mini, ERR_MALLOC);
		}
	}
	else
		ret->value = 0;
	ret->next = NULL;
	return (ret);
}

void	add_envelem(t_mini *mini, char *key, char *value)
{
	t_env	*ret;
	t_env	*tmp;

	if (mini->myenv == 0)
	{
		init_myenv(mini, key, value);
		return ;
	}
	tmp = mini->myenv;
	ret = init_envelem(mini, key, value);
	while (mini->myenv->next != NULL)
		mini->myenv = mini->myenv->next;
	mini->myenv->next = ret;
	mini->myenv = tmp;
}

int	get_env(char **env, t_mini *mini)
{
	char	*key;
	char	*value;
	int		i;
	int		j;

	i = -1;
	if (!env || !*env)
		return (0);
	while (env[++i])
	{
		j = 0;
		while (env[i][j] != 0 && env[i][j] != '=')
			j++;
		key = ft_substr(env[i], 0, j);
		if (env[i][j + 1] != '\0')
			value = ft_substr(env[i], j + 1, ft_strlen(env[i]));
		else
			value = NULL;
		add_envelem(mini, key, value);
		free(key);
		free(value);
	}
	mini->environment = env;
	return (1);
}
