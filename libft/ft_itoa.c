/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 14:06:07 by ggobert           #+#    #+#             */
/*   Updated: 2021/12/09 15:42:54 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int	positron(int n)
{
	long int	l;

	l = n;
	if (l < 0)
		return (-1);
	return (1);
}

int	intlen(int n)
{
	long int	l;
	int			len;

	len = 0;
	l = n;
	if (positron(l) < 0)
		len++;
	l *= positron(l);
	while (l > 9)
	{
		l /= 10;
		len++;
	}
	len++;
	return (len);
}

char	*ft_itoa(int n)
{
	char		*ret;
	int			i;
	long int	l;
	int			count;

	l = (long int) n;
	i = 0;
	count = intlen(l);
	ret = malloc(sizeof(char) * (count + 1));
	if (ret == NULL)
		return (NULL);
	if (l == 0)
		ret[0] = '0';
	if (positron(l) < 0)
		ret[i++] = '-';
	l *= positron(l);
	ret[count] = 0;
	while (count-- > i)
	{
		ret[count] = l % 10 + '0';
		l /= 10;
	}
	return (ret);
}

/*int	main(void)
{
	printf("%s\n", ft_itoa(123LL));
	return (0);
}*/
