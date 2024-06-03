#include "../../include/minishell.h"

void	handle_line(char *line, int file)
{
	ft_putstr_fd(line, file);
	ft_putchar_fd('\n', file);
	free(line);
}

int	is_line_delimiter(char *line, t_redir_node *redir_node)
{
	size_t	line_len;
	size_t	delimiter_len;

	if (!line)
	{
		printf("Debug: line is NULL\n");
		return (0);
	}
 	if (*line == '\0')
	{
		printf("Debug: line is empty\n");
		return (0);
	}
	line_len = ft_strlen(line);
	delimiter_len = ft_strlen(redir_node->file);
	if (ft_strncmp(line, redir_node->file, delimiter_len) == 0 
			&& (line_len == delimiter_len))
		return (1);
	else
		return (0);
}
