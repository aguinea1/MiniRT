/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <aguinea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:07:16 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/16 17:04:14 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dest == src || !n)
		return (dest);
	if (dest < src)
	{
		while (i < n)
		{
			*((char *)dest + i) = *((char *)src + i);
			i++;
		}
	}
	else
	{
		while (n > 0)
		{
			*((char *)dest + n - 1) = *((char *)src + n -1);
			n--;
		}
	}
	return (dest);
}
/*
#include <stdio.h>
int	main(void)
{
	char	src[] = "ABCDE";
	char	src2[] = "ABCDEvkvhvbjhvb";
	char	dest[10];

	ft_memmove(src, src + 2, 7);
//dest < src --> copia CDE en ABC (no sobreposicion)
	printf("%s\n", src);
	ft_memmove(src2 + 2, src2, 10);
//dest > src --> copia ABC en CDE empezando por la C (para evitar sobreposicion)
	printf("%s\n", src2);
	return (0);
}*/
