/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:08:06 by gdaignea          #+#    #+#             */
/*   Updated: 2023/10/13 17:28:42 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*str;

	i = 0;
	if (start >= ft_strlen((char *)s))
		return (ft_calloc(1, sizeof (char)));
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	str = malloc(sizeof (char) * (len + 1));
	if (!str)
		return (NULL);
	while (s[start] && i < len)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

/*
int	main(void)
{
	const char	s[] = "Hello World";
	char	*toto; 
	
	toto = ft_substr(s, 3, 5);
	printf ("%s\n", toto);
	free(toto);
	return (0);
}*/
