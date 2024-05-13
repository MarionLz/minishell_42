/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 15:34:43 by gdaignea          #+#    #+#             */
/*   Updated: 2023/11/15 17:53:45 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nb_digit(long int nb)
{
	int	i;

	i = 0;
	if (nb < 0)
	{
		nb = -nb;
		i++;
	}
	while (nb > 9)
	{
		nb /= 10;
		i++;
	}
	return (i + 1);
}

char	*ft_itoa(int n)
{
	long int	nb;
	int			i;
	char		*str;

	nb = n;
	i = nb_digit(nb);
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	str[i--] = '\0';
	if (nb < 0)
		nb = -nb;
	while (i >= 0)
	{
		str[i--] = (nb % 10) + '0';
		nb /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

/* int	main(void)
{
	int	c = 0;
	int d = -2147483648;
	int e = -2547;
	char	*str1 = ft_itoa(c);
	char	*str2 = ft_itoa(d);
	char	*str3 = ft_itoa(e);
	
	printf("%s\n", str1);
	printf("%s\n", str2);
	printf("%s\n", str3);
	free (str1);
	free (str2);
	free (str3);
	return (0);
} */