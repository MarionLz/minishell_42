#include "../../include/minishell.h"

/* is_quotes : return true if the character is a simple or a double quote
and return false if not.*/
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
If yes, the function prints an error message and returns true.*/
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

/*is_token_with_quotes : take a look in the token to check if it contains quotes.
Return true if it contains quotes, return false if not.*/
bool	is_token_with_quotes(char *input)
{
	while (*input && !is_whitespace(*input) && !is_symbol(*input))
	{
		if (is_quotes(*input))
			return (true);
		input++;
	}
	return (false);
}
/*inside_quotes : check if we are inside quotes.
Return true if count_quotes is odd : it means that quotes are open.*/
bool	inside_quotes(int count_quotes)
{
	if (count_quotes % 2 != 0)
		return (true);
	return (false);
}
