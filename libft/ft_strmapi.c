/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 13:55:37 by ggobert           #+#    #+#             */
/*   Updated: 2021/12/07 14:24:16 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char		*k;
	int			i;

	i = 0;
	if (!s)
		return (0);
	k = malloc(sizeof(char) * (ft_strlen((char *)s) + 1));
	if (k == 0)
		return (0);
	while (s[i])
	{
		k[i] = f(i, s[i]);
		i++;
	}
	k[i] = 0;
	return ((char *)k);
}
