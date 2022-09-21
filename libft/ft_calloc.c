/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 11:31:30 by ggobert           #+#    #+#             */
/*   Updated: 2021/12/07 12:15:16 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	*ft_calloc(size_t count, size_t size)
{
	char	*ret;
	size_t	i;

	i = 0;
	ret = malloc(size * count);
	if (ret == NULL)
		return (NULL);
	while (size * count > i)
		ret[i++] = 0;
	return ((void *) ret);
}

/*int	main()
{
	int c = 5;
	int *array = calloc(sizeof(int), c);

	while (c)
		printf("%d ", array[c--]);
	return (0);
}*/
