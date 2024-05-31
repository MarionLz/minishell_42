/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 09:52:58 by gdaignea          #+#    #+#             */
/*   Updated: 2023/11/08 14:36:57 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_fd(int fd, char *stash)
{
	int		bytes_read;
	char	*buf;

	bytes_read = 1;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (bytes_read > 0 && !ft_strchr(stash, '\n'))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == 0 && ft_strlen(stash))
			break ;
		if (bytes_read <= 0)
		{
			free(buf);
			free(stash);
			return (NULL);
		}
		buf[bytes_read] = '\0';
		stash = ft_strjoin_and_free(stash, buf);
	}
	free(buf);
	return (stash);
}

char	*free_stash(char *stash)
{
	char	*temp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	if (!stash[i])
	{
		free (stash);
		return (NULL);
	}
	if (stash[i] == '\n')
		i++;
	temp = malloc(sizeof(char) * ((ft_strlen(stash) - i) + 1));
	if (!temp)
		return (NULL);
	while (stash[i])
		temp[j++] = stash[i++];
	temp[j] = '\0';
	free(stash);
	return (temp);
}

char	*extract_line(char *stash)
{
	char	*line;
	int		i;
	int		len_line;

	i = 0;
	len_line = 0;
	while (stash[len_line] != '\n' && stash[len_line])
		len_line++;
	line = malloc(sizeof(char) * (len_line + 2));
	if (!line)
		return (NULL);
	while (stash[i] != '\n' && stash[i])
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n' && stash[i])
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	stash = read_fd(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = free_stash(stash);
	return (line);
}

/*int	main(void)
{
	char	*content;
	int fd = open("cat.txt", O_RDONLY);
	
	// content = get_next_line(fd);
	// while (ft_strlen(content))
	// {
	// 	printf("%s", content);
	// 	free(content);
	// 	content = get_next_line(fd);
	// }
	// free(content);
	
	while(1)
	{
		content = get_next_line(fd);
		if(!content)
		{
			break;
		}
		printf("%s", content);
		free(content);
	}
	if (content)
		free(content);
	close(fd);
	return (0);
}*/
