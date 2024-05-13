/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:26:55 by gdaignea          #+#    #+#             */
/*   Updated: 2023/10/13 11:38:58 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	sc;
	unsigned int	i;

	str = (unsigned char *) s;
	sc = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (str[i] == sc)
			return (str + i);
		i++;
	}
	return (NULL);
}
