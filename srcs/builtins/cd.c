/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:49:48 by ggobert           #+#    #+#             */
/*   Updated: 2022/09/29 17:58:14 by ggobert          ###   ########.fr       */
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

char	*get_path(char **av)
{
	char	*path;
	char	*path_slash;
	char	*tmp;

	if (*av[1] == '/')
		return (ft_strdup(av[1]));
	else
	{
		path = get_pwd();
		tmp = ft_strjoin(path, "/");
		free(path);
		path_slash = ft_strjoin(tmp, av[1]);
		free(tmp);
		return (path_slash);
	}
}

char	*back_repo(char *curpath)
{
	int		i;
	int		counter;

	counter = 2;
	i = ft_strlen(curpath);
	while (curpath[i] != '.')
		i--;
	while (counter)
		if (curpath[i--] == '/')
			counter--;
	return (ft_substr(curpath, 0, i + 1));
}

char	*two_dot(char *curpath)
{
	int		i;

	i = -1;
	while (curpath[++i])
		if (curpath[i] == '.' && curpath[i + 1])
			if (curpath[i + 1] == '.')
				return (back_repo(curpath));
	return (curpath);
}

void	push_in_env(t_mini *mini, char *curpath)
{
	t_env	*tmp;
	char	*temp;
	
	tmp = mini->myenv;
	temp = two_dot(curpath);
	while (tmp)
	{
		if (!ft_strncmp("PWD", tmp->key, str_big("PWD", tmp->key)))
		{
			free(tmp->value);
			tmp->value = ft_strdup(temp);
		}
		tmp = tmp->next;
	}
}

void	cd(t_mini *mini, int ac, char **av)
{
	char	*curpath;

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
	if (chdir(curpath) < 0)
	{
		if (errno == 20)
			write_error_message(ERR_NOFILE);
		printf("\nNop...\n\n");
	}
	else
		push_in_env(mini, curpath);
	if (ac != 1)
		free (curpath);
}
