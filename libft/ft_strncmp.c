/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 11:12:25 by ggobert           #+#    #+#             */
/*   Updated: 2021/12/03 12:38:19 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int	ft_strncmp(const char *first, const char *second, size_t length)
{
	if ((!*first && !*second) || !length)
		return (0);
	length--;
	while (*first == *second && *first && *second && length--)
	{
		first++;
		second++;
	}
	return ((unsigned char) *first - (unsigned char)*second);
}

/*int main(int ac, char **av)
{
	(void)ac;
	printf("%d", ft_strncmp(av[1], av[2], 7));
	return (0);
}*/
