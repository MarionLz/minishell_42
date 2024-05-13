/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gautier <gautier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:35:15 by gdaignea          #+#    #+#             */
/*   Updated: 2024/02/02 11:35:00 by gautier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elementCount, size_t size)
{
	char	*str;
	int		total_size;

	total_size = size * elementCount;
	if (size != 0 && total_size / size != elementCount)
		return (NULL);
	str = malloc(sizeof(char) * total_size);
	if (!str)
		return (NULL);
	ft_bzero(str, total_size);
	return (str);
}
