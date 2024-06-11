/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdaignea <gdaignea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:03:55 by gdaignea          #+#    #+#             */
/*   Updated: 2024/06/11 19:14:48 by gdaignea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

# define MAX_ARGS 100

//variable globale
extern int	g_exit_status;

typedef enum s_tokentype
{
	EXEC,
	PIPE,
	REDIR,
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
	int		r_type;
	t_node	*cmd;
	char	*file;
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

/* MAIN */
void	ft_error(char *error);
bool	contain_only_whitespace(char *input);
int		is_input_empty(char *input, t_data *data);
void	*input_handler(char *input, t_data *data);

/* ENV */
int		tab_len(char **tab);
char	**dup_env(char **env);
bool	valid_num_content(char *str);
char	**increase_shell_level(t_data *data);
t_data	*handle_env(char **data);

/* PARSING */
t_node	*parse_error(char *message);
t_node	*parse_redir(t_node *node, char **start_scan, char *end_input,
			t_data *data);
t_node	*parse_exec(char **start_scan, char *end_input, t_data *data);
t_node	*parse_pipe(char **start_scan, char *end_input, t_data *data);
t_node	*parse_input(char *input, t_data *data);

/* CLEAN INPUT */
char	*make_new_input(char *new_input, char **input);
char	*skip_quotes_to_ignore(char **input, char *new_input, t_data *data);
char	*delimit_token(char *new_input, bool *open_tok, char quote);
char	*cleaner(char *new_input, char *input, t_data *data);
char	*clean_input(char *input, t_data *data);

/* REPLACE_DOLLAR */
char	*get_exit_status(char *new_input);
char	*get_var_name(t_dollar *var, char **input);
bool	find_var_in_env(t_dollar *var, t_data *data);
char	*copy_var_value(t_dollar *var, char *new_input, t_data *data);
char	*replace_dollar(char *new_input, char **input, t_data *data);

/* TOKEN */
int		insight_input(char **start_token, char *end_input, char *target);
int		get_type_redir(char **str, int type);
int		get_type(char **str, int type, char *end_input);
int		token_with_quotes(char **str, char **start_token, char **end_token);
int		get_token(char **start_scan, char *end_input, char **start_token,
			char **end_token);

/* CREATE_NODES */
void	fill_args(t_exec_node *exec_node, char *start_token, char *end_token,
			int *i);
t_node	*create_redir_node(int token_type, t_node *cmd, char *start_file,
			char *end_file);
t_node	*create_pipe_node(t_node *left, t_node *right);
t_node	*create_exec_node(void);

/* REDIR UTILS */
void	init_fd_and_mode(int token_type, t_redir_node	*redir_node);
t_node	*multiple_redir(t_node *cmd, t_redir_node *last_redir);

/* QUOTES UTILS */
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
int		check_next_token(char *start_scan, char *end_input);

/* NULTERMINATE */
void	nulterminate_exec_node(t_data *data, t_exec_node *exec_node);
t_node	*nulterminate(t_node *tree, t_data *data);

/* RUN */
int		ft_fork(void);
int		is_cmd_env_builtin(t_node *tree);
void	run(t_node *tree, t_data *data);
void	fork_before_exec(t_node *tree, t_data *data);
void	check_and_run(t_node *tree, t_data *data);

/* RUN BUILTIN */
void	run_builtin(char **args, t_data *data);

/* RUN REDIR */
void	reopen_stdin_stdout(int fd);
void	run_heredoc(t_redir_node *redir_node);
void	run_redir(t_node *tree, t_data *data);
void	ft_heredoc(t_redir_node *redir_node);

/* RUN UTILS */
void	handle_line(char *line, int file);
int		is_line_delimiter(char *line, t_redir_node *redir_node);
void	dup_right(int *fd);

/* RUN PIPE */
void	run_next_node_left(t_pipe_node *pipe_node, int *fd, t_data *data);
void	run_next_node_right(t_pipe_node *pipe_node, int *fd, t_data *data);
int		wait_for_process(pid_t pid1);
int		is_there_heredoc(t_node *node);
int		run_pipe(t_node *tree, t_data *data);

/* RUN EXEC */
void	free_tab(char **tab);
char	*extract_env(char **env);
char	*get_path(char *cmd, t_data *data);
void	run_exec(t_node *tree, t_data *data);

/* CD */
char	*get_home_folder(t_data *data);
int		change_directory(char *path);
void	actualize_env(char *directory, char *var, t_data *data);
int		go_home(t_data *data, char *old_directory);
void	ft_cd(char **args, t_data *data);

/* ECHO */
bool	is_empty_quotes(char *str);
void	print_args(char **args, int i);
void	ft_echo(char **args);

/* ENV */
void	ft_env(t_data *data);

/* EXIT */
void	actualize_status_and_exit(char *status);
void	ft_exit(char **args);
int		is_input_exit(char *input, t_data *data);
void	ft_exit_and_free(char **input_cpy, t_data *data);

/* EXPORT */
int		is_var_valid(char *args);
int		does_var_exist(char *var, t_data *data);
void	add_new_var(char *var, t_data *data);
void	change_var(char *var, t_data *data);
void	ft_export(char **args, t_data *data);

/* PWD */
void	ft_pwd(void);

/* UNSET */
bool	is_var_name_valid(char **args);
int		find_var_to_delete(char *env, char **args);
char	*copy_variable(char *to_copy, char **new_env, int j);
void	ft_unset(char **args, t_data *data);

/* SIGNALS */
void	setup_heredoc_signals(void);
void	setup_main_signals(void);
void	signal_routine(int signal);
void	heredoc_handler(int signal);
void	signal_routine_child(int signal);

/* UTILS */
char	*ft_strnjoin(char *s1, char *s2, int n);
bool	is_whitespace(char c);
bool	is_symbol(char c);
void	skip_whitespace(char **input);

/* FREE */
void	free_env(t_data *data);
void	free_tree(t_node *tree);
void	*free_tab_until_n(char **env, int n);

#endif