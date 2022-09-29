/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 15:38:35 by ggobert           #+#    #+#             */
/*   Updated: 2022/09/29 14:26:01 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
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
	printf("%s\n", path);
	free(path);
}