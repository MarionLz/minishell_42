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

# define MAX_ARGS 50

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
	IN_REDIR,
	OUT_REDIR,
	HEREDOC,
	APPEND,
}	t_tokentype;

typedef struct s_data
{
	char	**env_cpy;
	int		nb_cmd;
	char	*new_input;
	int		stdin_cpy;
	int		stdout_cpy;
}	t_data;

typedef struct s_dollar
{
	char	*name;
	int		len_name;
	int		index;
}	t_dollar;

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
	char	*file;
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

/* ENV */
int		tab_len(char **tab);
char	**dup_env(char **env);
bool	valid_num_content(char *str);
char 	**increase_shell_level(t_data *data);
t_data	*handle_env(char **data);

/* PARSING */
t_node	*parse_exec(char **start_scan, char *end_input);
t_node	*nulterminate(t_node *tree, t_data *data);
t_node	*parse_input(char *input, t_data *data);

/* CLEAN INPUT */
char	*clean_input(char *input, t_data *data);

/* REPLACE_DOLLAR */
char	*replace_dollar(char *new_input, char **input, t_data *data);

/* TOKEN */
int		insight_input(char **start_token, char *end_input, char *target);
int		get_type(char **str, int type, char *end_input);
int		get_token(char **start_scan, char *end_input, char **start_token, char **end_token);

/* CREATE_NODES */
t_node	*create_redir_node(int token_type, t_node *cmd, char *start_file, char *end_file);
t_node	*create_pipe_node(t_node *left, t_node *right);
t_node	*create_exec_node(void);

/* QUOTES */
bool	is_quotes(char c);
void	check_quotes(int *simple_quote, int *double_quotes, char *input, int i);
bool	open_quotes(char *input);
bool	is_token_with_quotes(char *input, char *quote_type);
bool	inside_quotes(int count_quotes);

/* PARSING_UTILS */
int		compare_cmd(char *str1, char *str2, int n);
bool	is_builtin(char *cmd);
char	*strjoin_char(char *s1, char c);
bool	empty_pipe(char *input);
int	check_for_double_pipe(char *start_scan, char *end_input);

/* NULTERMINATE */
void	nulterminate_exec_node(t_data *data, t_exec_node *exec_node);
t_node	*nulterminate(t_node *tree, t_data *data);

/* RUN */
int		ft_fork(void);
void	run(t_node *tree, t_data *data);
void	check_and_run(t_node *tree, t_data *data);

/* RUN BUILTIN */
void	run_builtin(char **args, t_data *data);

/* RUN REDIR */
void	handler_heredoc(int signal);
void	reopen_stdin_stdout(int fd);
void	run_redir(t_node *tree, t_data *data);
void	ft_heredoc(t_redir_node *redir_node);

/* HERE DOC UTILS */
void	handle_line(char *line, int file);
int		is_line_delimiter(char *line, t_redir_node *redir_node);

/* RUN PIPE */
int		run_pipe(t_node *tree, t_data *data);

/* RUN EXEC */
void	free_tab(char **tab);
void	run_exec(t_node *tree, t_data *data);

/* BUILTINS */
void	ft_cd(char **args, t_data *data);
void	ft_pwd(void);
void	ft_env(t_data *data);

/* ECHO */
bool	is_empty_quotes(char *str);
void	print_args(char **args, int i);
void	ft_echo(char **args);

/* EXIT */
void	actualize_status_and_exit(char *status);
void	ft_exit(char **args);
void	is_input_exit(char *input, t_data *data);
void	ft_exit_and_free(char **input_cpy, t_data *data);

/* EXPORT */
int		is_var_valid(char *args);
int		does_var_exist(char *var, t_data *data);
void	add_new_var(char *var, t_data *data);
void	change_var(char *var, t_data *data);
void	ft_export(char **args, t_data *data);

/* UNSET */
void	ft_unset(char **args, t_data *data);

/* SIGNALS */
void	setup_heredoc_signals(void);
void	setup_main_signals(void);
void	signal_routine(int signal);
void	heredoc_handler(int signal);

/* UTILS */
char	*ft_strnjoin(char *s1, char *s2, int n);
bool	is_whitespace(char c);
bool	is_symbol(char c);

/* FREE */
void	free_env(t_data *data);
void	free_tree(t_node *tree);
void	*free_tab_until_n(char **env, int n);

#endif