/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 13:01:51 by ggobert           #+#    #+#             */
/*   Updated: 2021/12/08 11:18:23 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*ret;
	int					i;

	i = 0;
	if (!s)
		return (0);
	if (ft_strlen((char *)s) <= start)
		len = 0;
	if (len > ft_strlen((char *)s))
		len = ft_strlen((char *)s);
	ret = malloc(sizeof(char) * (len + 1));
	if (ret == NULL)
		return (NULL);
	while (len-- && s[start])
	{
		ret[i] = s[start];
		i++;
		start++;
	}
	ret[i] = 0;
	return (ret);
}

/*int main()
{
	int		len = 0;
	char	*str = "0123456789";
	
	printf("%s", ft_substr(str, 2, 5));
	return (0);
}*/
