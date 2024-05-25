#include "../../include/minishell.h"

/* insight_input : Check if the beginning of the token contains any of the characters contained in target.
It iterates through the input as long as the read character is a whitespace.
It updates the start_scan pointer (the beginning of the new token).
It returns true if any of the characters contained in target are found. */

int	insight_input(char **start_scan, char *end_input, char *target)
{
	char *str;

	str = *start_scan;
	while (str < end_input && is_whitespace(*str))
		str++;
	*start_scan = str;
	return (*str && ft_strchr(target, *str));
}

/* get_type : initialise the type of the token. */

void	get_type(char **str, int *type, char *end_input, char quote)
{
	if (**str == '|' && quote == 0)
	{
		*type = PIPE;
		(*str)++;
	}
	else if (**str == '<' && quote == 0)
	{
		(*str)++;
		if (**str == '<')
		{
			*type = HEREDOC;
			(*str)++;
		}
		else
			*type = IN_REDIR;
	}
	else if (**str == '>' && quote == 0)
	{
		(*str)++;
		if (**str == '>')
		{
			*type = APPEND;
			(*str)++;
		}
		else
			*type = OUT_REDIR;
	}
	else
	{
		*type = EXEC;
		if (quote == 0)
		{
			while (*str < end_input && !is_whitespace(**str) && !is_symbol(**str) && !is_quotes(**str))
				(*str)++;
		}
		else
			while (*str < end_input && **str != quote)
				(*str)++;
	}
}

/* get_token : Scan the input, locate the position of the next token, and initialize its type.
start_scan: pointer to where to begin scanning.
end_input: pointer to the end of the input.
start_token and end_token: pointers to the beginning and end of the found token.
Reposition the start_token pointer to the beginning of the next token. */

int	get_token(char **start_scan, char *end_input, char **start_token, char **end_token)
{
	char	*str;
	int		type;
	char	quote;

	str = *start_scan;
	quote = 0;
	while (str < end_input && is_whitespace(*str))
		str++;
	if (str >= end_input)
		return (-1);
	if (is_quotes(*str))
	{
		quote = *str;
		*start_token = str;
		str++;
		if (*str == quote)
		{
			str++;
			*end_token = str;
			while (str < end_input && is_whitespace(*str))
				str++;
			*start_scan = str;
			return (EXEC);
		}
	}
	if (start_token)
		*start_token = str;
	get_type(&str, &type, end_input, quote);
	if (end_token)
		*end_token = str;
	if (is_quotes(*str))
		str++;
	while (str < end_input && is_whitespace(*str))
		str++;
	*start_scan = str;
	return (type);
}
