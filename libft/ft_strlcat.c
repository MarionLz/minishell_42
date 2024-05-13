/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:20:54 by gdaignea          #+#    #+#             */
/*   Updated: 2023/10/12 15:16:20 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	len_dst;
	unsigned int	len_src;

	i = 0;
	j = 0;
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	while (dst[i] && i < size)
		i++;
	if (size < len_dst || size <= 0)
		return (len_src + size);
	while (src[j] && i < (size - 1))
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (len_dst + len_src);
}
