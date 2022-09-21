/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobert <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 11:13:54 by ggobert           #+#    #+#             */
/*   Updated: 2021/12/02 18:28:43 by ggobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*str;

	str = (char *) s;
	while (n--)
	{
		if (*str == (char) c)
			return ((void *) str);
		str++;
	}
	return (0);
}

/*int main()
{
	char data[] = {22, 15, 19, 58};
	size_t len = 4;
	int c = 18;
	int	i = 0;
	char *found = ft_memchr(data, c, len);
	
	while (found[i])
		printf("%d ", *(found + i++));
	puts("");
	return (0);
}

int main() 
{
    char data[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };
    const unsigned int size = 10;

    void * found = memchr( data, 57, size );
    printf( "57 is %s\n", ( found != NULL ? "found" : "not found" ) );

    found = memchr( data, 100, size );
    printf( "100 is %s\n", ( found != NULL ? "found" : "not found" ) );
    if ( found != NULL ) 
	{
        printf( "La valeur à la position calculée est %d\n", *((char *) found) );
    }

    return EXIT_SUCCESS;
}*/
