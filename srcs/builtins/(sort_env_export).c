/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:08:10 by ggobert           #+#    #+#             */
/*   Updated: 2022/09/28 12:10:07 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_env_export(t_mini *mini)
{
	t_env		*tmp_env;
	//t_export	*tmp_exp;

	tmp_env = mini->myenv;
	//tmp_exp = mini->myexport;
	init_sort(mini);
	while (tmp_env)
	{
		sort_env(tmp_env, mini);
		tmp_env = tmp_env->next;
	}
}

void	sort_env(t_env *env, t_mini *mini)
{
	t_sort	*previous;

	previous = 0;
	while (mini->sort->previous)
		mini->sort = mini->sort->previous;
	while (env)
	{
		while (sort_ascii(mini->sort->key, env->key) < 2 && mini->sort->next)
			mini->sort = mini->sort->next;
		previous = mini->sort;
		if (sort_ascii(mini->sort->key, env->key) == 2)
		{
			if (mini->sort->previous)
				sort_front(mini, mini->sort, env->key, env->value);
			else
				sort_between(mini, mini->sort, env->key, env->value, previous);
		}
		if (!mini->sort->next)
			sort_back(mini ,mini->sort, env->key, env->value, previous);
		env = env->next;
	}	
}

int	sort_ascii(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1 || !str2)
		return (0);
	while (str1[i] && str2[i])
	{
		if (str1[i] - str2[i] < 0)
			return (1);
		if (str1[i] - str2[i] > 0)
			return (2);
		i++;
	}
	if	(str1[i])
		return (2);
	if	(str2[i])
		return (1);
	return (0);
}

void	init_sort(t_mini *mini)
{
	char	*key;
	char	*value;
	if (mini->myenv)
	{
		key = ft_strdup(mini->myenv->key);
		value = ft_strdup(mini->myenv->value);
	}
	else if (mini->myexport)
	{
		key = ft_strdup(mini->myexport->key);
		value = 0;
	}
	mini->sort = malloc(sizeof(t_sort));
	if (!mini->sort)
		free_mini_exit_msg(mini, ERR_MALLOC);
	mini->sort->key = ft_strdup(key);
	mini->sort->value = ft_strdup(value);
	mini->sort->next = 0;
	mini->sort->previous = 0;
}

void    sort_between(t_mini *mini, t_sort *sort, char *key, char *value, t_sort *previous)
{
	t_sort   *ret;

	ret = malloc(sizeof(t_env));
	if (!ret)
		free_mini_exit_msg(mini, ERR_MALLOC);
	ret->key = ft_strdup(key);
	ret->value = ft_strdup(value);
	ret->next = sort;
	if (!ret->key || !ret->value)
		free_mini_exit_msg(mini, ERR_MALLOC);
	sort->previous = ret;
	sort->previous->previous = previous;
}

void	sort_back(t_mini *mini, t_sort *sort, char *key, char *value, t_sort *previous)
{
	t_sort   *ret;

	ret = malloc(sizeof(t_env));
	if (!ret)
		free_mini_exit_msg(mini, ERR_MALLOC);
	ret->key = ft_strdup(key);
	ret->value = ft_strdup(value);
	ret->next = 0;
	ret->previous = previous;
	if (!ret->key || !ret->value)
		free_mini_exit_msg(mini, ERR_MALLOC);
	sort->next = ret;
}

void	sort_front(t_mini *mini, t_sort *sort, char *key, char *value)
{
	t_sort   *ret;

	ret = malloc(sizeof(t_env));
	if (!ret)
		free_mini_exit_msg(mini, ERR_MALLOC);
	ret->key = ft_strdup(key);
	ret->value = ft_strdup(value);
	ret->next = sort;
	ret->previous = 0;
	if (!ret->key || !ret->value)
		free_mini_exit_msg(mini, ERR_MALLOC);
}
