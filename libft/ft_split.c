/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gautier <gautier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 09:42:20 by gdaignea          #+#    #+#             */
/*   Updated: 2024/04/03 11:29:07 by gautier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	*ft_strndup(const char *s, int n)
{
	char	*dst;
	int		i;

	i = 0;
	dst = (char *)ft_calloc(n + 1, sizeof(char));
	if (!dst)
		return (NULL);
	while (i < n)
	{
		dst[i] = s[i];
		i++;
	}
	return (dst);
}

static void	mallocsecure(char **tab, int j)
{
	while (j)
	{
		j--;
		free(tab[j]);
	}
	free(tab);
}

static char	**fill_tab(char **tab, const char *s, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		k = i;
		while (s[i] != c && s[i])
			i++;
		if (i > k)
		{
			tab[j] = ft_strndup(&s[k], (i - k));
			if (!tab[j])
			{
				mallocsecure(tab, j);
				return (NULL);
			}
			j++;
		}
	}
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**str;

	str = (char **)ft_calloc(count_words(s, c) + 1, sizeof(char *));
	if (!str)
		return (NULL);
	str = fill_tab(str, s, c);
	return (str);
}
