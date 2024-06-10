/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:02:34 by gdaignea          #+#    #+#             */
/*   Updated: 2024/06/10 17:03:38 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strnjoin(char *s1, char *s2, int n)
{
	char	*str;
	int		totalsize;
	int		i;
	int		j;

	i = 0;
	j = 0;
	totalsize = (n + ft_strlen(s2));
	str = malloc((sizeof (char)) * totalsize + 1);
	if (!str)
		return (NULL);
	while (i < n)
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
	free(s2);
	return (str);
}

bool	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (true);
	return (false);
}

bool	is_symbol(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

//norminette bullshit adjustment (cf clean_input.c)
void	skip_whitespace(char **input)
{
	while (**input && is_whitespace(**input))
		(*input)++;
}
