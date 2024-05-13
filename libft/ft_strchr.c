/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 09:55:57 by gdaignea          #+#    #+#             */
/*   Updated: 2023/10/13 11:10:24 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ((char) c))
			return ((char *)str + i);
		i++;
	}
	if ((char) c == '\0')
		return ((char *)str + i);
	return (NULL);
}

/*int	main(void)
{
	const char	str[] = "bonjour";
	int	c = 366;
	
	printf("%s\n", ft_strchr(str, c));
	printf("%s\n", strchr(str, c));
	return (0);
}*/