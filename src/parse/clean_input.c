#include "../../include/minishell.h"

/*int	insight_input(char **start_scan, char *end_input, char *target)
{
	char *str;

	str = *start_scan;
	while (str < end_input && is_whitespace(*str))
		str++;
	*start_scan = str;
	return (*str && ft_strchr(target, *str));
}*/

/*void	insight_quotes(char **input, char *target)
{

}*/

char	*clean_quotes(char *input)
{
	static char	new_input[200];
	int		count_quotes;
	char	quote;
	int		i;

	i = 0;
	while (*input && is_whitespace(*input))
		input++;
	while (*input)
	{
		if (is_quotes(*input))
		{
			while (*input && is_quotes(*input))
			{
				count_quotes = 0;
				quote = *input;
				while (*input == quote)
				{
					input++;
					count_quotes++;
				}
				if (count_quotes % 2 != 0)
					break;
			}
			if (count_quotes % 2 != 0)
			{

				while (*input != quote)
				{
					new_input[i] = *input;
					printf("char = %c\n", *input);
					input++;
					i++;
				}
			}
		}
		if (!is_quotes(*input))
		{
			new_input[i] = *input;
			printf("char = %c\n", *input);
			input++;
			i++;
		}
		else
			input++;
	}
	new_input[i] = '\0';
	printf("new_input = %s\n", new_input);
	input = new_input;
	return (input);
}

char	*clean_input(char *input)
{
	if (open_quotes(input) == true)
		return (NULL);
	input = clean_quotes(input);
	return (input);
}
