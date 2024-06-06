#include "../../include/minishell.h"

void	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while(data->env_cpy[i])
	{
		printf("%s\n", data->env_cpy[i]);
		i++;
	}
}