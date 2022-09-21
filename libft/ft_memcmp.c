/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:03:44 by ggobert           #+#    #+#             */
/*   Updated: 2021/12/06 10:28:05 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while (n--)
	{
		if (*str1 - *str2 == 0)
		{
			str1++;
			str2++;
		}
		else
			return (*str1 - *str2);
	}
	return (0);
}

/*int	main()
{
	ft_memcmp("bonjour", "condour", 10);
}*/

/*int main()
{
	int		array1 [] = {10, 15, 20, 25};
	int		array2 [] = {10, 15, 19, 30};
	size_t	size = sizeof(int) * 4;
	assert( memcmp( array1, array2, size) == ft_memcmp( array1, array2, size) );
    assert( memcmp( array1, array1, size) == ft_memcmp( array1, array1, size) );
    assert( memcmp( array2, array1, size) == ft_memcmp( array2, array1, size) ); 
    printf( "Test is ok\n" );    
    return 0;
}*/
