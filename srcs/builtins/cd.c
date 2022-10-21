/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:49:48 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/21 16:30:03 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(char **args)
{
	char	*path;
	char	*path_slash;
	char	*tmp;

	if (*args[1] == '/')
		return (ft_strdup(args[1]));
	else
	{
		path = get_pwd();
		tmp = ft_strjoin(path, "/");
		free(path);
		path_slash = ft_strjoin(tmp, args[1]);
		free(tmp);
		return (path_slash);
	}
}

char	*back_repo(char *curpath, int dot_count)
{
	int		i;
	char	*tmp;

	i = 0;
	while (curpath[i] && curpath[i] != '.')
		i++;
	while (dot_count)
		if (curpath[i] && curpath[i--] == '/')
			dot_count--;
	tmp = ft_substr(curpath, 0, i + 1);
	free(curpath);
	return (tmp);
}

char	*two_dot(char *curpath)
{
	int		i;
	int		dot_count;
	char	*tmp;

	dot_count = 1;
	i = -1;
	while (curpath[++i])
		if (curpath[i] == '.' && curpath[i + 1])
			if (curpath[++i] == '.')
				dot_count++;
	if (dot_count == 1)
	{
		tmp = ft_strdup(curpath);
		return (tmp);
	}
	tmp = back_repo(curpath, dot_count);
	return (tmp);
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
	free(temp);
}

void	cd(t_command *cmd, t_mini *mini)
{
	char	*curpath;

	old_pwd(mini);
	if (cmd_args_len(cmd) == 1)
		curpath = home_env(mini);
	else if (cmd_args_len(cmd) > 2)
	{
		write_error_message(ERR_ARG);
		return ;
	}
	else
		curpath = get_path(cmd->args);
	if (chdir(curpath) < 0)
	{
		g_exit_status = 1;
		perror(NULL);
	}
	else
		push_in_env(mini, curpath);
}

/* Les erreurs gérées sont : 
		fichier inexistant
		non-droit sur un dossier
		element du path n'est pas un dossier
Pas de leaks, point et 2points gérés 
NON GEREE : cd dans un dossier puis le suppr (comportement indefini) */