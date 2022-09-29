/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:34:16 by gregoiregob       #+#    #+#             */
/*   Updated: 2022/09/29 15:56:36 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_big(char *a, char *b)
{
	if (ft_strlen(a) > ft_strlen(b))
		return (ft_strlen(a));
	else
		return (ft_strlen(b));
}

void	lst_del_unset_env(t_env *tmp, t_env *previous)
{
	if (tmp->key)
		free(tmp->key);
	if (tmp->value)
		free(tmp->value);
	if (previous)
		previous->next = tmp->next;
	free(tmp);
}

void	lst_del_unset_export(t_export *tmp, t_export *previous)
{
	if (tmp->key)
		free(tmp->key);
	if (previous)
		previous->next = tmp->next;
	free(tmp);
}


void	unset_in_env(t_mini *mini, char **av)
{
	int		i;
	t_env	*tmp;
	t_env	*previous;

	i = 1;
	previous = 0;
	tmp = mini->myenv;
	while (tmp)
	{
		if (ft_strncmp(av[i], tmp->key, str_big(av[i], tmp->key)) != 0)
		{
			previous = tmp;
			tmp = tmp->next;
		}
		else
		{
			lst_del_unset_env(tmp, previous);
			tmp = previous;
		}
	}
	i++;
}

void	unset_in_export(t_mini *mini, char **av)
{
	int			i;
	t_export	*tmp;
	t_export	*previous;

	i = 1;
	previous = 0;
	tmp = mini->myexport;
	while (tmp)
	{
		if (ft_strncmp(av[i], tmp->key, str_big(av[i], tmp->key)) != 0)
		{
			previous = tmp;
			tmp = tmp->next;
		}
		else
		{
			lst_del_unset_export(tmp, previous);
			if (!previous)
				mini->myexport = 0;
			tmp = previous;
		}
	}
	i++;
}

void	unset(t_mini *mini, int ac, char **av)
{
	if (ac == 1)
		write_error_message("not enough arguments");
	while (ac-- > 1)
	{
		unset_in_env(mini, av);
		unset_in_export(mini, av);
	}
}
