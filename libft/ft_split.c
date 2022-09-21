/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:44:07 by ggobert           #+#    #+#             */
/*   Updated: 2021/12/08 11:00:50 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

int	countwords(const char *s, char c)
{
	int	words;

	words = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
			words++;
		while (*s != c && *s)
			s++;
	}
	return (words);
}

int	countlett(const char *s, char c)
{
	int	lett;

	lett = 0;
	while (*s != c && *s)
	{
		s++;
		lett++;
	}
	return (lett);
}

int	securemalloc(char **tab, int j)
{
	if (tab[j] == 0)
	{
		while (j >= 0)
			free(tab[j--]);
		return (1);
	}
	return (0);
}

char	**undertab(char **tab, const char *s, char c)
{
	int	i;
	int	j;

	j = 0;
	while (*s)
	{
		i = 0;
		while (*s == c && *s)
			s++;
		if (*s)
		{
			tab[j] = malloc(sizeof(char) * (countlett(s, c) + 1));
			if (securemalloc(tab, j) == 1)
				return (NULL);
			while (*s != c && *s)
				tab[j][i++] = *s++;
			tab[j++][i] = 0;
		}
	}
	tab[j] = 0;
	return (tab);
}

char	**ft_split(const char *s, char c)
{
	char	**tab;

	if (!s)
		return (0);
	tab = malloc(sizeof(char *) * (countwords(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	return (undertab(tab, s, c));
}
