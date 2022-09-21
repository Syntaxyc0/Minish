/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 19:02:46 by ggobert           #+#    #+#             */
/*   Updated: 2021/12/03 12:16:40 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strrchr(const char *s, int c)
{
	int	l;

	l = 1;
	while (*s)
	{
		l++;
		s++;
	}
	while (l--)
	{
		if (*s == (unsigned char) c)
			return ((char *) s);
		s--;
	}
	return (0);
}

/*int main()
{
	char	*str = "fulltifme";
	int c = 'f';

	printf("%s", ft_strrchr(str, c));
	return(0);
}*/
