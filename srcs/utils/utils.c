/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 14:26:11 by ggobert           #+#    #+#             */
/*   Updated: 2022/10/20 14:44:14 by ggobert          ###   ########.fr       */
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

void	get_all_path(t_mini *mini)
{
	t_env	*ev;

	ev = mini->myenv;
	while (ft_strncmp(ev->key, "PATH", str_big(ev->key, "PATH")))
		ev = ev->next;
	mini->all_path = ft_split(ev->value, ':');
}
