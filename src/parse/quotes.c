#include "../../include/minishell.h"

bool	is_quotes(char c)
{
	if (c == '"' || c == '\'')
		return (true);
	return (false);
}

/*check_quotes : when there is a double quote or a single quote, this function analyses
if it's an open or a closed quote (1 = open, 0 = close).*/
void	check_quotes(int *simple_quote, int *double_quotes, char *input)
{
	if (*input == '"')
	{
		if (!*simple_quote && !*double_quotes)
			*double_quotes = 1;
		else
			*double_quotes = 0;
	}
	if (*input == '\'')
	{
		if (!*double_quotes && !*simple_quote)
			*simple_quote = 1;
		else
			*simple_quote = 0;
	}
}

/*open_quotes : browses the input and checks if there are open quotes.
If yes, it prints an error message.*/
bool	open_quotes(char *input)
{
	int	simple_quote;
	int	double_quotes;

	simple_quote = 0;
	double_quotes = 0;
	while (*input)
	{
		check_quotes(&simple_quote, &double_quotes, input);
		input++;
	}
	if (simple_quote || double_quotes)
	{
		printf("Error, open quotes\n");
		return (true);
	}
	return (false);
}
