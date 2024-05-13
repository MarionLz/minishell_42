/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 10:39:48 by gdaignea          #+#    #+#             */
/*   Updated: 2023/10/13 11:10:10 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		size;
	char	*ptr;

	size = ft_strlen(str);
	ptr = (char *) str;
	if (!c)
		return (&ptr[size]);
	while (size >= 0)
	{
		if (ptr[size] == (char)c)
			return (&ptr[size]);
		size--;
	}
	return (0);
}

/*int	main(void)
{
	const char	str[] = "bonjonr";
	int	c = 'n' + 256;
	const char str2[] = "bonjour";
	int	d = 'b';
	
	printf("%s\n", ft_strrchr(str, c));
	printf("%s\n", strrchr(str, c));
	printf("\n");
	printf("%s\n", ft_strrchr(str2, d));
	printf("%s\n", strrchr(str2, d));
	return (0);
}*/