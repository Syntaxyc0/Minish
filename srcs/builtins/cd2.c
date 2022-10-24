/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 13:40:01 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/24 16:39:47 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(t_mini *mini)
{
	int		i;
	char	*path;

	i = 256;
	path = malloc(i);
	if (!path)
	{
		g_exit_status = 1;
		free_mini_exit_msg(mini, ERR_MALLOC);
	}
	while (getcwd(path, i) == 0)
	{
		free(path);
		i *= 2;
		path = malloc(i);
		if (!path)
		{
			g_exit_status = 1;
			free_mini_exit_msg(mini, ERR_MALLOC);
		}
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
			home_path = ft_strdup(tmp->value);
			if (!home_path)
			{
				g_exit_status = 1;
				free_mini_exit_msg(mini, ERR_MALLOC);
			}
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

	path = get_pwd(mini);
	tmp = mini->myenv;
	while (tmp)
	{
		if (!ft_strncmp("OLDPWD", tmp->key, str_big("OLDPWD", tmp->key)))
		{
			free(tmp->value);
			tmp->value = ft_strdup(path);
			if (!tmp->value)
			{
				g_exit_status = 1;
				free_mini_exit_msg(mini, ERR_MALLOC);
			}
		}
		tmp = tmp->next;
	}
	free(path);
}

char	*get_path(char **args, t_mini *mini)
{
	char	*path;
	char	*path_slash;
	char	*tmp;

	path = 0;
	path_slash = 0;
	tmp = 0;
	if (*args[1] == '/')
		return (ft_strdup(args[1]));
	else
	{
		path = get_pwd(mini);
		if (!path)
			exit_free_status_msg(mini, 1, ERR_MALLOC);
		tmp = ft_strjoin(path, "/");
		if (!tmp)
			exit_free_status_msg(mini, 1, ERR_MALLOC);
		free(path);
		path_slash = ft_strjoin(tmp, args[1]);
		if (!path_slash)
			exit_free_status_msg(mini, 1, ERR_MALLOC);
		free(tmp);
		return (path_slash);
	}
}
