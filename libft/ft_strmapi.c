/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:06:55 by gdaignea          #+#    #+#             */
/*   Updated: 2023/10/13 15:54:05 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	i = 0;
	str = malloc((sizeof (char)) * ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*char	fttoupper(unsigned int n, char c)
{
	(void)n;
	if (c >= 'a' && c <= 'z')
		c = c - 32;
	return (c);
}

int	main (void)
{
	const char	s[] = "hello world !";
	char	*tab = ft_strmapi(s, fttoupper);
	
	printf("%s\n", tab);
	free (tab);
	return (0);
}*/