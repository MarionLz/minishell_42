#include "../../include/minishell.h"

void	ft_env(t_env *env)
{
	int	i;

	i = 0;
	while(env->env_cpy[i])
	{
		printf("%s\n", env->env_cpy[i]);
		i++;
	}
}