#include "../../include/minishell.h"

/* insight_input : Check if the beginning of the next token contains any of the characters contained in target.
It iterates through the input as long as the read character is a whitespace.
It updates the start_token pointer (the beginning of the new token).
It returns true if any of the characters contained in target are found. */

int	insight_input(char **start_token, char *end_input, char *target)
{
	char *str;

	str = *start_token;
	while (str < end_input && is_whitespace(*str))
		str++;
	*start_token = str;
	return (*str && ft_strchr(target, *str));
}

/* get_type : initialise the type of the token. s*/

void	get_type(char **str, int *type, char *end_input)
{
	if (**str == '|')
	{
		*type = PIPE;
		(*str)++;
	}
	else if (**str == '<')
	{
		if (**str++ == '<')
			*type = HEREDOC;
		else
			*type = IN_REDIR;
	}
	else if (**str == '>')
	{
		if (**str++ == '>')
			*type = APPEND;
		else
			*type = OUT_REDIR;
	}
	else
	{
		*type = (EXEC);
		while (*str < end_input && !is_whitespace(**str) && !is_symbol(**str))
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

	str = *start_scan;
	while (str < end_input && is_whitespace(*str))
		str++;
	*start_token = str;
	if (!str)
		type = -1;
	get_type(&str, &type, end_input);
	*end_token = str;
	while (str < end_input && is_whitespace(*str))
		str++;
	*start_scan = str;
	return (type);
}
