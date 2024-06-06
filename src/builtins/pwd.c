#include "../../include/minishell.h"

void	ft_pwd(void)
{
	char	*directory;

	directory = NULL;
	directory = getcwd(directory, 0);
	if (directory == NULL)
		ft_error("pwd");
	printf("%s\n", directory);
	free(directory);
}
