/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 11:49:48 by ggobert           #+#    #+#             */
/*   Updated: 2022/11/01 11:36:33 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*back_repo(char *curpath, int dot_count, t_mini *mini)
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
	if (!tmp)
	{
		g_exit_status = 1;
		free_mini_exit_msg(mini, ERR_MALLOC);
	}
	free(curpath);
	return (tmp);
}

char	*two_dot(char *curpath, t_mini *mini)
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
		if (!tmp)
		{
			g_exit_status = 1;
			free_mini_exit_msg(mini, ERR_MALLOC);
		}
		free(curpath);
		return (tmp);
	}
	tmp = back_repo(curpath, dot_count, mini);
	return (tmp);
}

void	push_in_env(t_mini *mini, char *curpath)
{
	t_env	*tmp;
	char	*temp;

	tmp = mini->myenv;
	temp = two_dot(curpath, mini);
	while (tmp)
	{
		if (!ft_strncmp("PWD", tmp->key, str_big("PWD", tmp->key)))
		{
			free(tmp->value);
			tmp->value = ft_strdup(temp);
			if (!tmp->value)
			{
				g_exit_status = 1;
				free_mini_exit_msg(mini, ERR_MALLOC);
			}
		}
		tmp = tmp->next;
	}
	free(temp);
}

void	cd(t_command *cmd, t_mini *mini)
{
	char	*curpath;

	g_exit_status = 0;
	old_pwd(mini);
	if (cmd_args_len(cmd) == 1)
		curpath = home_env(mini);
	else if (cmd_args_len(cmd) > 2)
	{
		g_exit_status = 1;
		write_error_message(ERR_ARG);
		return ;
	}
	else
	{
		curpath = get_path(cmd->args, mini);
		if (!curpath)
		{
			g_exit_status = 1;
			free_mini_exit_msg(mini, ERR_MALLOC);
		}
	}
	chdir_res(curpath, mini);
}

void	chdir_res(char *curpath, t_mini *mini)
{
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