/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 14:28:39 by ggobert           #+#    #+#             */
/*   Updated: 2021/12/02 12:27:04 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *dest, int val, size_t len)
{
	unsigned char	*ptr;

	ptr = dest;
	while (len--)
		*ptr++ = val;
	return (dest);
}
