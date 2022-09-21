/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 15:27:51 by ggobert           #+#    #+#             */
/*   Updated: 2021/12/09 15:44:25 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*k;

	if (!*lst)
		return ;
	k = (*lst)->next;
	while (*lst)
	{
		k = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = k;
	}
}
