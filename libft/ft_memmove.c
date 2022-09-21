/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 15:17:48 by ggobert           #+#    #+#             */
/*   Updated: 2021/12/06 10:26:49 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*s;
	char		*d;
	char		*lastd;
	char		*lasts;

	s = src;
	d = dest;
	lastd = NULL;
	lasts = NULL;
	if (!d && !s)
		return (0);
	if (d < s)
		while (n--)
			*d++ = *s++;
	else
	{
		lastd = d + (n - 1);
		lasts = (char *) s + (n - 1);
		while (n--)
			*lastd-- = *lasts--;
	}
	return (dest);
}

/*int main()
{
	int	data[] = {1, 2, 3, 4, 5};
	int	len = 0;
	size_t	size = sizeof(int) * 5;

	while (len < 5)
		printf("%d ", data[len++]);
	puts("");
	void	*dest = data + 1;
	void	*src = data ;
	ft_memmove(dest, src, size);
	data[4] = 7;
	data[3] = 6;
	len = 0;
	while (len < 5)
		printf("%d ", data[len++]);
	puts("");
	return (0);	
}*/
