#include "../../include/minishell.h"

void	skip_quotes_to_ignore(char **input, char *new_input, int *i)
{
	int		count_quotes;
	char	quote_type;

	while (**input && is_quotes(**input))
	{
		count_quotes = 0;
		quote_type = **input;
		while (**input == quote_type)
		{
			(*input)++;
			count_quotes++;
		}
		if (inside_quotes(count_quotes))
		{
			while (**input != quote_type)
			{
				new_input[*i] = **input;
				(*i)++;
				(*input)++;
			}
			(*input)++;
		}
	}
}

void	delimit_token_with_quotes(char *new_input, int *i, bool *open_tok)
{
	new_input[*i] = '"';
	(*i)++;
	if (*open_tok == true)
		*open_tok = false;
	else
		*open_tok = true;
}

char	*clean_quotes(char *input)
{
	static char	new_input[200];
	int			i;
	bool		open_tok;

	i = 0;
	open_tok = false;
	while (*input && is_whitespace(*input))
		input++;
	while (*input)
	{
		if (is_token_with_quotes(input) && open_tok == false)
			delimit_token_with_quotes(new_input, &i, &open_tok);
		if (is_quotes(*input))
			skip_quotes_to_ignore(&input, new_input, &i);
		if (*input && !is_quotes(*input))
		{
			if (open_tok == true && (is_whitespace(*input) || is_symbol(*input)))
				delimit_token_with_quotes(new_input, &i, &open_tok);
			new_input[i++] = *input++;
		}
	}
	if (open_tok == true)
		new_input[i++] = '"';
	new_input[i] = '\0';
	return (new_input);
}

char	*clean_input(char *input)
{
	if (open_quotes(input) == true)
		return (NULL);
	input = clean_quotes(input);
	return (input);
}
