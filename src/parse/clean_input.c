#include "../../include/minishell.h"

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
				{
					new_input = strjoin_char(new_input, **input);
					(*input)++;
				}
			}
			(*input)++;
		}
	}
	return (new_input);
}

char	*delimit_token_with_quotes(char *new_input, bool *open_tok, char quote)
{
	new_input = strjoin_char(new_input, quote);
	if (*open_tok == true)
		*open_tok = false;
	else
		*open_tok = true;
	return (new_input);
}

char	*clean_quotes(char *input, t_env *env)
{
	bool	open_tok;
	char	*new_input;
	char	quote;

	open_tok = false;
	new_input = ft_strdup("");
	quote = 0;
	while (*input && is_whitespace(*input))
		input++;
	while (*input)
	{
		if (is_token_with_quotes(input, &quote) && open_tok == false)
			new_input = delimit_token_with_quotes(new_input, &open_tok, quote);
		if (is_quotes(*input))
			new_input = skip_quotes_to_ignore(&input, new_input, env);
		if (*input && !is_quotes(*input))
		{
			if (open_tok == true && (is_whitespace(*input) || is_symbol(*input)))
				new_input = delimit_token_with_quotes(new_input, &open_tok, quote);
			if (*input == '$')
				new_input = replace_dollar(new_input, &input, env);
			new_input = strjoin_char(new_input, *input);
			input++;
		}
	}
	if (open_tok == true)
		new_input = delimit_token_with_quotes(new_input, &open_tok, quote);
	new_input = strjoin_char(new_input, '\0');
	return (new_input);
}

char	*clean_input(char *input, t_env *env)
{	
	(void)env;
	if (open_quotes(input) == true)
		return (NULL);
	input = clean_quotes(input, env);
	return (input);
}
