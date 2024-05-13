/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:12:10 by gdaignea          #+#    #+#             */
/*   Updated: 2023/10/11 16:17:27 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	nb;

	nb = n;
	if (nb < 0)
	{
		nb = -nb;
		ft_putchar_fd('-', fd);
	}
	if (nb > 9)
		ft_putnbr_fd((nb / 10), fd);
	ft_putchar_fd((nb % 10 + '0'), fd);
}

/*int	main(void)
{
	int	i = 47821;
	int	j = -251486;
	int	k = -2147483648;
	
	ft_putnbr_fd(i, 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(j, 1);
	ft_putchar_fd('\n', 1);
	ft_putnbr_fd(k, 1);
	return(0);
}*/