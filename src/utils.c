#include "../include/minishell.h"

char *ft_strnjoin(char *s1, char *s2, int n)
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