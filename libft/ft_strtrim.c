/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 13:31:59 by ggobert           #+#    #+#             */
/*   Updated: 2021/12/17 16:19:59 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int	trimstart(const char *s1, const char *set)
{
	int		i;
	int		j;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while (set[j])
		{
			if (set[j] != s1[i])
				j++;
			else
				break ;
		}
		if (!set[j])
			return (i);
		i++;
	}
	return (i);
}

int	trimend(const char *s1, const char *set)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
		i++;
	i--;
	while (i > 0)
	{
		j = 0;
		while (set[j])
		{
			if (set[j] != s1[i])
				j++;
			else
				break ;
		}
		if (!set[j])
			return (i);
		i--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	int		j;
	int		i;
	int		k;

	j = 0;
	if (!s1)
		return (0);
	k = trimend(s1, set) - trimstart(s1, set);
	if (trimend(s1, set) - trimstart(s1, set) < 0)
		k = 0;
	ret = malloc(sizeof(char) * (k + 2));
	if (ret == NULL)
		return (NULL);
	i = trimstart(s1, set);
	while (i <= trimend (s1, set))
	{
		ret[j] = s1[i];
		i++;
		j++;
	}
	ret[j] = 0;
	return (ret);
}

/*int main(int ac, char **av)
{
	(void)ac;
	printf("%s", ft_strtrim(av[1], av[2]));
	return (0);
}*/
