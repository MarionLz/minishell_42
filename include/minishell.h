#ifndef MINISHELL
# define MINISHELL

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define MAX_ARGS 10

typedef enum s_tokentype
{
	EXEC,
	CMD,
	ARG,
	ENV_VAR,
	PIPE,
	IN_REDIR,		/* < */
	OUT_REDIR,		/* > */
	HEREDOC,		/* << */
	APPEND,			/* >> */
}	t_tokentype;

typedef struct s_node
{
	int	type;
}	t_node;

typedef struct s_exec_node
{
	int		type;
	char	*args[MAX_ARGS];
	char	*end_args[MAX_ARGS];
}	t_exec_node;

typedef struct s_redir_node
{
	int		type;
	t_node	*node;
	char 	*file;
	char	*end_file;
	int		mode;
	int		fd;
}	t_redir_node;

typedef struct s_pipe_node
{
	int		type;
	t_node	*left;
	t_node	*right;
}	t_pipe_node;

/* PARSING */
t_node	*parse_input(char *input);

/* RUN */
void	run(t_node *tree, char **env);

#endif