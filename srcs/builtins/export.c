/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:44:07 by ggobert           #+#    #+#             */
/*   Updated: 2022/11/07 14:40:29 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	import(t_mini *mini, int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (!check_arg(av[i]))
		{
			if (is_space_before_egal(av[i]))
			{
				printf("export: not valid in this context\n");
				return ;
			}
			if (is_egal(av[i]))
				import_env(mini, av[i]);
			else
				import_export(mini, av[i]);
		}
	}
}

void	import_export(t_mini *mini, char *s)
{
	t_export	*tmp;
	t_export	*ret;

	if (!mini->myexport)
	{
		init_myexport(mini, s);
		return ;
	}
	if (already_in_export(mini, s))
		return ;
	tmp = mini->myexport;
	ret = malloc(sizeof(t_export));
	if (!ret)
	{
		g_exit_status = 1;
		free_mini_exit_msg(mini, ERR_MALLOC);
	}
	ret->key = ft_strdup(s);
	ret->next = 0;
	while (mini->myexport->next)
		mini->myexport = mini->myexport->next;
	mini->myexport->next = ret;
	mini->myexport = tmp;
}

void	import_env(t_mini *mini, char *s)
{
	int		j;
	char	*key;
	char	*value;

	j = 0;
	while (s[j] && s[j] != '=')
		j++;
	key = ft_substr(s, 0, j);
	if (!key)
		exit_free_status_msg(mini, 1, ERR_MALLOC);
	if (s[j + 1])
	{
		value = ft_substr(s, j + 1, ft_strlen(s));
		if (!value)
			exit_free_status_msg(mini, 1, ERR_MALLOC);
	}	
	else
		value = 0;
	if (already_in_env(mini, key, value))
		;
	else
		add_envelem(mini, key, value);
	free(key);
	free(value);
}

int	check_arg(char *args)
{
	int	i;

	if (args[0] == '=')
	{
		write_error_message(ERR_VALIDARG);
		return (1);
	}
	i = 0;
	while (args[i] != '=' && args[i])
	{
		if (ft_isalpha(args[0]) != 1 && args[i] != '_')
		{
			write(1, "'", 2);
			write_error_message(args);
			write_error_message("' : ");
			write_error_message(ERR_VALIDARG);
			return (1);
		}
		i++;
	}
	return (0);
}

void	export(t_mini *mini, t_command *cmd)
{
	g_exit_status = 0;
	if (cmd_args_len(cmd) == 1)
		write_error_message("Unspecified behaviour (cf man export)\n");
	else
		import(mini, cmd_args_len(cmd), cmd->args);
}
