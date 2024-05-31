/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:52:10 by gdaignea          #+#    #+#             */
/*   Updated: 2024/05/30 18:13:49 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*ft_strjoin_and_free(char *s1, char *s2)
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
	free(s1);
	return (str);
}

