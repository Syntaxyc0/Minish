/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:37:33 by ggobert           #+#    #+#             */
/*   Updated: 2021/12/17 16:27:35 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	char	*s;
	size_t	i;

	s = (char *)src;
	i = 0;
	while (*src++)
		i++;
	if (!dstsize)
		return (i);
	dstsize--;
	while (dstsize-- && *s)
		*dst++ = *s++;
	*dst = '\0';
	return (i);
}

/*int main(int ac, char **av)
{
	(void)ac;
	printf("%ld", ft_strlcpy(av[1], av[2], 10));
	return (0);
}*/
