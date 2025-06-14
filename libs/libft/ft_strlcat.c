/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <aguinea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:07:16 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/16 17:04:14 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;

	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	if (dst == NULL && !size)
		return (len_src);
	if (size <= len_dst)
		return (len_src + size);
	else
		size -= len_dst;
	ft_strlcpy (dst + len_dst, src, size);
	return (len_src + len_dst);
}
/*
#include <stdio.h>

int	main(void)
{
	char	dst[] = "HGF";
	char	src[] = "Mundo";

	printf("%ld\n", ft_strlcat(dst, src, 1));
	printf("%s\n", dst);
	return (0);
}*/
