/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:31:49 by gdaignea          #+#    #+#             */
/*   Updated: 2023/10/20 15:32:22 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

int	get_start(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (is_set(s1[i], set) && s1[i])
		i++;
	return (i);
}

int	get_end(char const *s1, char const *set)
{
	int	j;

	j = ft_strlen(s1) - 1;
	while (is_set(s1[j], set) && j > 0)
		j--;
	return (j);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		len;
	int		k;
	char	*str;

	start = get_start(s1, set);
	end = get_end(s1, set);
	len = end - start;
	if (len == (int) ft_strlen(s1) || len < 0)
		return (ft_strdup(""));
	str = malloc(sizeof(char) * len + 2);
	if (!str)
		return (NULL);
	k = 0;
	while (k <= len && s1[start])
		str[k++] = s1[start++];
	str[k] = '\0';
	return (str);
}

/*int	main(void)
{
	const char	s1[] = "awxlxa";
	char	*str = ft_strtrim(s1, "awx");
	
	printf("%s\n", str);
	free(str);
	return (0);
}*/