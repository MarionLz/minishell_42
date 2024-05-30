#include "../../include/minishell.h"

/*make_new_input : copies the input character by character into the new input.*/

char	*make_new_input(char *new_input, char **input)
{
	new_input = strjoin_char(new_input, **input);
	(*input)++;
	return (new_input);
}

/*skip_quotes_to_ignore : skips over quotes that are not read (one or more pairs of empty quotes at the beginning, middle, or end of a token).
If it encounters quotes with content, it copies everything between these quotes into the new input, without copying the quotes. If it encounters a $, it calls replace_dollar, which will replace the environment variable with its content only if double quotes are open.*/

char	*skip_quotes_to_ignore(char **input, char *new_input, t_env *env)
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
				if (**input == '$' && quote_type == '"')
					new_input = replace_dollar(new_input, input, env);
				if (**input != quote_type)
					new_input = make_new_input(new_input, input);
			}
			(*input)++;
		}
	}
	return (new_input);
}

/*delimit_token : used to delimit with quotes the beginning and end of a token containing quotes so that the parser treats everything within these quotes as part of the same token.
Example: echo bonjour" ca va? | oui" will be delimited as follows: "bonjour ca va? | oui".*/

char	*delimit_token(char *new_input, bool *open_tok, char quote)
{
	new_input = strjoin_char(new_input, quote);
	if (*open_tok == true)
		*open_tok = false;
	else
		*open_tok = true;
	return (new_input);
}

/*cleaner : the function processes the input, cleans and replaces certain elements, and returns the new cleaned input.
- it starts by skipping all the whitespaces at the beginning of the input.
- it checks if the current token contains at least one pair of quotes. If so, it delimits the beginning of the token by adding a quote (to ensure that the parser will take the entire token) and indicates that a token is being read (open_tok).
- if the character read is a quote, it calls the skip_quotes_to_ignore function, which will clean the token of unnecessary quotes and copy the token's content into the new input.
- if the character read is not a quote:
	- if a token containing quotes is being read and this is the end of the token (space or symbol), it delimits the end of the token by adding a quote.
	- if the character read is a dollar sign, it calls the replace_dollar function, which will replace the environment variable with its content.
	- it continues to fill the new input.
Once at the end of the input, it delimits the end of the token by adding a quote if necessary and adds a '\0' to define the end of the new input.*/

char	*cleaner(char *new_input, char *input, t_env *env)
{
	bool	open_tok;
	char	quote;

	open_tok = false;
	quote = 0;
	while (*input && is_whitespace(*input))
		input++;
	while (*input)
	{
		if (is_token_with_quotes(input, &quote) && open_tok == false)
			new_input = delimit_token(new_input, &open_tok, quote);
		if (is_quotes(*input))
			new_input = skip_quotes_to_ignore(&input, new_input, env);
		if (*input && !is_quotes(*input))
		{
			if (open_tok == true && (is_whitespace(*input) || is_symbol(*input)))
				new_input = delimit_token(new_input, &open_tok, quote);
			if (*input == '$')
				new_input = replace_dollar(new_input, &input, env);
			new_input = make_new_input(new_input, &input);
		}
	}
	if (open_tok == true)
		new_input = delimit_token(new_input, &open_tok, quote);
	return (new_input = strjoin_char(new_input, '\0'));
}

/*clean_input : checks that there are no open quotes and calls the function that will clean the input.*/

char	*clean_input(char *input, t_env *env)
{
	bool	open_tok;
	char	*new_input;
	char	quote;

	open_tok = false;
	new_input = ft_strdup("");
	quote = 0;
	if (open_quotes(input) == true)
	{
		free_env(env);
		exit (EXIT_FAILURE);
	}
	return (new_input = cleaner(new_input, input, env));
}
