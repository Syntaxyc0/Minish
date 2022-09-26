/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 13:44:07 by ggobert           #+#    #+#             */
/*   Updated: 2022/09/26 15:05:01 by ggobert          ###   ########.fr       */
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

void	export(t_mini *mini, int ac, char **av)
{
	if (ac < 2)
		sort_env_export(mini)
	else
		import(mini, ac, av);
}

void	import(t_mini *mini, int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (is_egal(av[i]))
			import_env(mini, ac, av);
		else
			import_export(mini, ac, av)
	}
}

void	import_env(t_mini *mini, int ac, char **av)
{
	int		i;
	int		j;
	t_env	*cursor;
	char	*key;
	char	*value;

	i = 0;
	cursor = mini->myenv;
	while (cursor)
		cursor = cursor->next;
	while (++i < ac)
	{
		j = 0;
		while(av[i][j] != 0 && av[i][j] != '=')
            j++;
        key = ft_substr(av[i], 0, j);
		if (av[i][j + 1] != 0)
            value = ft_substr(av[i], j + 1, ft_strlen(av[i]));
        else
            value = 0;
		add_envelem(mini, key, value);
		free(key);
		free(value);
	}
}