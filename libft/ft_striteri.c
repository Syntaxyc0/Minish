/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 12:01:22 by ggobert           #+#    #+#             */
/*   Updated: 2021/12/08 12:06:21 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_striteri(char const *s, void (*f)(unsigned int, char*))
{
	char	*k;
	int		i;

	i = 0;
	if (!s)
		return ;
	k = (char *)s;
	while (s[i])
	{
		f(i, k++);
		i++;
	}
}
