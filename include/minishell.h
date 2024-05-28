#ifndef MINISHELL
# define MINISHELL

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

# define MAX_ARGS 10

//variable globale
extern	int		exit_status;

typedef enum s_tokentype
{
	EXEC,
	CMD,
	ARG,
	ENV_VAR,
	PIPE,
	REDIR,
	BUILTIN,
	IN_REDIR,		/* < */
	OUT_REDIR,		/* > */
	HEREDOC,		/* << */
	APPEND,			/* >> */
}	t_tokentype;

typedef struct s_env
{
	char	**env_cpy;
	int		nb_cmd;
}	t_env;

typedef struct s_node
{
	int	type;
}	t_node;

typedef struct s_exec_node
{
	int		type;
	bool	is_builtin;
	char	*args[MAX_ARGS];
	char	*end_args[MAX_ARGS];
}	t_exec_node;

typedef struct s_redir_node
{
	int		type;
	t_node	*cmd;
	char 	*file;
	char	*end_file;
	int		mode;
	int		fd;
	bool	is_heredoc;
}	t_redir_node;

typedef struct s_pipe_node
{
	int		type;
	t_node	*left;
	t_node	*right;
}	t_pipe_node;

/* MAIN */
void	ft_error(char *error);
char	**dup_env(char **env);

/* PARSING */
t_node	*parse_exec(char **start_scan, char *end_input);
t_node	*nulterminate(t_node *tree, t_env *env);
t_node	*parse_input(char *input, t_env *env);

/* CLEAN INPUT */
char	*clean_input(char *input, t_env *new_env);

/* REPLACE_DOLLAR */
char	*handle_dollar(char *input, char *new_input, t_env *new_env);

/* TOKEN */
int		insight_input(char **start_token, char *end_input, char *target);
void	get_type(char **str, int *type, char *end_input, char quote);
int		get_token(char **start_scan, char *end_input, char **start_token, char **end_token);

/* CREATE_NODES */
t_node	*create_redir_node(int token_type, t_node *cmd, char *start_file, char *end_file);
t_node	*create_pipe_node(t_node *left, t_node *right);
t_node	*create_exec_node();

/* QUOTES */
bool	is_quotes(char c);
void	check_quotes(int *simple_quote, int *double_quotes, char *input, int i);
bool	open_quotes(char *input);
bool	is_token_with_quotes(char *input);
bool	inside_quotes(int count_quotes);

/* PARSING_UTILS */
bool	is_whitespace(char c);
bool	is_symbol(char c);
int		compare_cmd(char *str1, char *str2, int n);
bool	is_builtin(char *cmd);

/* RUN */
int		ft_fork(void);
void	run(t_node *tree, t_env *env);
void	check_and_run(t_node *tree, t_env *env);

/* RUN BUILTIN */
void	run_builtin(char **args, t_env *env);

/* RUN REDIR */
void	reopen_stdin_stdout(int fd);
void	run_redir(t_node *tree, t_env *env);

/* RUN PIPE */
int	run_pipe(t_node *tree, t_env *env);

/* RUN EXEC */
void	free_tab(char **tab);
void	run_exec(t_node *tree, t_env *env);

/* BUILTINS */
void	ft_cd(char **args, t_env *env);
void	ft_pwd(void);
void	ft_env(t_env *env);

/* ECHO */
bool	is_empty_quotes(char *str);
void	print_args(char **args, int i);
void	ft_echo(char **args);

/* EXIT */
void	actualize_status_and_exit(char *status);
void	ft_exit(char **args);
void	is_input_exit(char *input);
void	ft_exit_and_free(char **input_cpy);


/* EXPORT */
int		is_var_valid(char *var);
int		does_var_exist(char *var, t_env *env);
void	add_new_var(char *var, t_env *env);
void	change_var(char *var, t_env *env);
void	ft_export(char **args, t_env *env);

/* UNSET */
void	ft_unset(char **args, t_env *env);

/* SIGNALS */
void	sigint_routine(int signal);
void	handle_sigint(void);
void	handle_sigquit(void);

#endif