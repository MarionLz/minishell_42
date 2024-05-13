/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:56:49 by gdaignea          #+#    #+#             */
/*   Updated: 2023/10/09 11:25:56 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		totalsize;
	int		i;
	int		j;

	i = 0;
	j = 0;
	totalsize = (ft_strlen(s1) + ft_strlen(s2));
	str = malloc((sizeof (char)) * totalsize + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

/*int	main(void)
{
	const char	s1[] = "hello ";
	const char	s2[] = "world !";
	char	*str = ft_strjoin(s1, s2);
	
	printf("%s\n", str);
	free(str);
	return (0);
}*/
