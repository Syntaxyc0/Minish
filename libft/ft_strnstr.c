/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:19:25 by ggobert           #+#    #+#             */
/*   Updated: 2021/12/17 16:19:48 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int	i;
	int	j;

	i = 0;
	if (!*needle || haystack == needle)
		return ((char *) haystack);
	while (len && haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && len - j && needle[j])
			j++;
		if (!needle[j])
			return ((char *) haystack + i);
		i++;
		len--;
	}
	return (0);
}

/*int main(int ac, char **av)
{
	(void)ac;
	printf("%s\n",ft_strnstr(av[1], av[2], 6));
	return (0);
}*/
