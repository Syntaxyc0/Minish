/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 14:44:05 by ggobert           #+#    #+#             */
/*   Updated: 2022/09/30 15:17:58 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(int ac, char **av)
{
	int	i;
	int	n_count;

	i = 1;
	n_count = 0;
	while (!ft_strncmp(av[i], "-n", str_big(av[i], "-n")))
	{
		n_count++;
		i++;
	}
	while (av[i])
	{
		if (i < ac)
		{
			printf("%s", av[i]);
			if (i != ac - 1)
				printf(" ");
		}
		i++;
	}
	if (!n_count)
		printf("\n");
}
