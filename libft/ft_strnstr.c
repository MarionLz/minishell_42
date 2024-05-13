/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 11:27:25 by y gdaignea        #+#    #+#             */
/*   Updated: 2023/10/13 15:17:10 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (!little[j])
		return ((char *)big + i);
	while (big[i] && i < len)
	{
		if (little[0] == big[i])
		{
			j = 0;
			while (big[i + j] == little[j] && i + j < len)
			{
				j++;
				if (little[j] == '\0')
					return ((char *)big + i);
			}
		}
		i++;
	}
	return (NULL);
}

/*int	main(void)
{
	const char	big[] = "A";
	//const char	little[] = "";
	size_t len = ft_strlen(big) + 1;
	
	printf("%s\n", ft_strnstr(big, big, len));
	return (0);
}*/