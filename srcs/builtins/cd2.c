/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:40:01 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/21 13:40:47 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*get_pwd(void)
{
	int		i;
	char	*path;

	i = 256;
	path = malloc(i);
	while (getcwd(path, i) == 0)
	{
		free(path);
		i *= 2;
		path = malloc(i);
	}
	return (path);
}

char	*home_env(t_mini *mini)
{
	char	*home_path;
	t_env	*tmp;

	tmp = mini->myenv;
	while (tmp->key)
	{
		if (!ft_strncmp("HOME", tmp->key, str_big("HOME", tmp->key)))
		{
			home_path = tmp->value;
			push_in_env(mini, home_path);
			return (home_path);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	old_pwd(t_mini *mini)
{
	char	*path;
	t_env	*tmp;

	path = get_pwd();
	tmp = mini->myenv;
	while (tmp)
	{
		if (!ft_strncmp("OLDPWD", tmp->key, str_big("OLDPWD", tmp->key)))
		{
			free(tmp->value);
			tmp->value = ft_strdup(path);
		}
		tmp = tmp->next;
	}
	free(path);
}