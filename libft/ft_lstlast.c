/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 14:57:38 by ggobert           #+#    #+#             */
/*   Updated: 2021/12/09 15:49:05 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int		i;
	t_list	*cursor;

	if (!lst)
		return (0);
	cursor = lst;
	i = ft_lstsize(lst);
	i--;
	while (i--)
		cursor = cursor->next;
	return (cursor);
}
