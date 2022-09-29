/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:44:07 by ggobert           #+#    #+#             */
/*   Updated: 2022/09/28 15:34:47 by ggobert          ###   ########.fr       */
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

void	import(t_mini *mini, int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (is_space_before_egal(av[i]) == 1)
		{
			printf("export: not valid in this context\n");
			return;
		}
		if (is_egal(av[i]))
			import_env(mini, av[i]);
		else
			import_export(mini, av[i]);
	}
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

void	import_export(t_mini *mini, char *s)
{
	t_export	*tmp;
	t_export	*ret;

	if (!mini->myexport)
	{
		init_myexport(mini, s);
		return;
	}
	tmp = mini->myexport;
	ret = malloc(sizeof(t_export));
	if (!ret)
		free_mini_exit_msg(mini, ERR_MALLOC);
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
	while(s[j] != 0 && s[j] != '=')
		j++;
	key = ft_substr(s, 0, j);
	if (s[j + 1])
		value = ft_substr(s, j + 1, ft_strlen(s));
	else
		value = 0;
	printf("value : %s\n", value);
	add_envelem(mini, key, value);
	free(key);
	free(value);
}

void	export(t_mini *mini, int ac, char **av)
{
	if (ac == 1)
		printf("cf man export\n");
	else
		import(mini, ac, av);
}