#include "../../include/minishell.h"

//A gerer = mise a jour de la variable env OLDPWD
void    ft_pwd(void)
{
	char *directory;

	directory = NULL;
	directory = getcwd(directory, 0);
	if (directory == NULL)
	{
		perror("pwd");
		return ;
	}
	printf("%s\n", directory);
	free(directory);
}