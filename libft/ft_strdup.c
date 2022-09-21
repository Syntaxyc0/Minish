/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 12:12:20 by ggobert           #+#    #+#             */
/*   Updated: 2021/12/17 16:19:12 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*ret;
	int		i;

	i = 0;
	len = 0;
	while (s1[i++])
		len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (len --)
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

/*int main()
{
	char	*str = "polol";
	int len = 0;

	while (len < 6)
		printf("%c", ft_strdup(str)[len++]);
	return (0);
}*/
