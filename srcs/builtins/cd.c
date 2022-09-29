/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:49:48 by ggobert           #+#    #+#             */
/*   Updated: 2022/09/29 15:54:45 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd(t_mini *mini, int ac, char **av)
{
	char	*curpath;

	curpath = 0;
	(void)av;
	old_pwd(mini);
	if (ac == 1)
		curpath = home_env(mini);
	else if (ac > 2)
	{
		write_error_message(ERR_ARG);
		return ;
	}
	else
		curpath = get_path(av);
	printf("___________________curpath = %s\n", curpath);
	if (chdir(curpath) < 0)
		printf("****ERROR*****\n");
	if (curpath)
		free(curpath);
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

char	*get_path(char **av)
{
	char	*path;
	char	*path_slash;

	if (*av[1] == '/')
		return (ft_strdup(av[1]));
	else
	{
		path = get_pwd();
		path_slash = ft_strjoin(path, "/");
		free(path);
		path_slash = ft_strjoin(path_slash, av[1]);
		return (path_slash);
	}
}

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