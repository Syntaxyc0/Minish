/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <ggobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:32:52 by ggobert           #+#    #+#             */
/*   Updated: 2022/07/22 14:19:39 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
		if (str[i++] == '\n')
			return (1);
	return (0);
}

int	ft_n_nl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		if (str[i++] == '\n')
			return (i);
	return (i);
}

char	*ft_read(char *show, int fd)
{
	int		count;
	char	*buf;

	count = BUFFER_SIZE;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (0);
	while (ft_nl(show) < 1 && count == BUFFER_SIZE)
	{
		count = read(fd, buf, BUFFER_SIZE);
		if (count < 1)
		{
			free(buf);
			return (show);
		}
		buf[count] = 0;
		show = ft_strjoin_g(show, buf);
	}
	free(buf);
	return (show);
}

char	*get_next_line(int fd)
{
	char		*show;
	static char	ret[BUFFER_SIZE + 1];

	if (fd < 0 || read(fd, ret, 0) < 0)
		return (0);
	show = ft_strdup("");
	if (*ret)
		show = ft_strjoin_g(show, ret);
	show = ft_read(show, fd);
	if (!*show)
	{
		free(show);
		return (0);
	}
	after_line(show, ret, ft_n_nl(show));
	show = cut_at(show, ft_n_nl(show));
	return (show);
}
