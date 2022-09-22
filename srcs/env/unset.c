/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gregoiregobert <gregoiregobert@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:34:16 by gregoiregob       #+#    #+#             */
/*   Updated: 2022/09/22 18:13:59 by gregoiregob      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	str_big(char *a, char *b)
{
	if (ft_strlen(a) > ft_strlen(b))
		return (ft_strlen(a));
	else
		return(ft_strlen(b));
}

void	lst_del_unset(t_env *tmp, t_env *previous)
{
	if (tmp->key)
		free(tmp->key);
	if (tmp->value)
		free(tmp->value);
	if (tmp->next)
		previous->next = tmp->next;
	else
		previous->next = 0;
	free(tmp);
}

void	unset(t_mini *mini, int ac, char **av)
{
	int		i;
	t_env	*tmp;
	t_env	*previous;

	i = 0;
	tmp = mini->myenv;
	//printf("myenv key = %s\n", tmp->key);
	previous = 0;
	if (!ac)
		write_error_message("not enough arguments");
	while (ac--)
	{
		while (tmp)
		{
			if (ft_strncmp(av[i], tmp->key, str_big(av[i], tmp->key)))
			{
				printf("strncmp %d\n", ft_strncmp(av[i], tmp->key, str_big(av[i], tmp->key)));
				previous = tmp;
				tmp = tmp->next;
			}
			else
			{
				printf("enter now_____________________________________\n");
				lst_del_unset(tmp, previous);
			}
		}
		i++;
	}
}
