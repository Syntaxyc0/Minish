/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:54:58 by ggobert           #+#    #+#             */
/*   Updated: 2021/12/07 15:11:10 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_atoi(const char *str)
{
	int	pos;
	int	ret;

	pos = 1;
	ret = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			pos *= -1;
	while (*str >= '0' && *str <= '9')
		ret = ret * 10 + (*str++ - '0');
	return (ret * pos);
}

/*int main (int ac, char ** av)
{
	(void)ac;
	printf("%d\n", ft_atoi(av[1]));
	return (0);
}*/
