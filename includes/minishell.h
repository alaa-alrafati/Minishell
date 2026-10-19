/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsbeh <hsbeh@student.42amman.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 14:01:43 by aalrofat          #+#    #+#             */
/*   Updated: 2026/05/16 13:22:51 by hsbeh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include "libft.h"
# include <stdio.h>
# include <unistd.h> //malloc,getcwd,dup
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

# ifndef STR_LONG_LONG_MAX
#  define STR_LONG_LONG_MAX "9223372036854775807"
# endif

# ifndef STR_LONG_LONG_MIN
#  define STR_LONG_LONG_MIN "9223372036854775808"
# endif

extern int	g_signal;

/*the struct of environment list*/
typedef struct s_envir
{
	char			*key;
	char			*value;
	struct s_envir	*next;
}	t_envir;

/*token struct lexer*/
typedef enum e_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HERE_DOC,
	APPEND
}	t_type;

typedef struct s_lexer
{
	char			*value;
	t_type			type;
	int				quote_type;
	struct s_lexer	*next;
}	t_lexer;

/*the command struct*/
typedef struct s_command
{
	char				**args;
	int					input_fd;
	int					output_fd;
	int					exit_num;
	pid_t				pid;
	struct s_command	*next;
}	t_command;

typedef struct s_shell
{
	t_envir			*env_list;
	t_lexer			*tokens;
	t_command		*commands;
	char			**envp;
	int				exit_status;
	int				stdout_origion;
	int				stdin_origion;
}	t_shell;

t_lexer	*make_new_node(char *str, t_type type);
void	add_token(t_lexer **tokens, t_lexer *new_node);
void	free_lexer(t_lexer **tokens);
void	free_commands(t_command **commands);
void	free_args(char **args);
int		main(int argc, char **argv, char **envp);
int		start_lexing(char *rl, t_shell *shell);
int		handle_special_redir_in(char *rl, int x, t_shell *shell);
int		handle_words(char *rl, int x, t_shell *shell);
int		clean_up_our_minishell(t_shell *shell);
int		lex_expand_and_parse(char *rl, t_shell *shell);

////expand
t_envir	*fill_envir_struct(char **envp);
t_envir	*creat_new_env_node(char *env_value, char *env_key);
void	start_expand(t_shell *shell);
void	free_for_expand(char *temp, char *val, char	*key);
char	*remove_quote(char *value);
char	*find_key(int *x, char *value);
int		check_quotations_and_update(int *quote, char x);

/*parser*/
void	connect_cmd_to_commands_shell(t_command *cmd, t_shell *shell);
void	syntax_error(t_lexer **current, t_shell *shell);
int		start_parsing(t_shell *shell);
int		fill_cmd_struct_data(t_command *cmd, t_lexer **current, t_shell *shell);
int		handle_here_doc(char *delimiter, t_command *cmd, t_shell *shell);
int		handle_redir3(int type, char *name_of_file,
			t_command *cmd, t_shell *shell);

/*execute*/
pid_t	simple_execution_cmd(t_shell *shell, t_command *cmd);
void	execution_controller(t_shell *shell, t_command *cmd);
void	link_node_from_end(t_envir **the_start_node, t_envir *new_node);
void	handle_exit_error(char *array_of_arg, t_shell *shell);
void	wait_child_processes(t_command *cmd, t_shell *shell);
void	handle_child_termination_signal(t_shell *shell, int return_status);
void	free_env(t_envir *the_start_node);
void	free_the_path(char **the_path);
void	close_original_fds(t_shell *shell);
void	restore_default_signals(void);
void	close_all_fds(t_shell *shell);
char	**convert_env_to_array(t_envir *env);
char	*free_path_and_return_null(char **cmd_path);
char	*free_and_return_path(char **cmd_path, char *path_with_cmd);
char	*check_cmd_path(char *cmd, char *envp[]);
int		free_value_key_return_one(char *env_value, char *env_key);
int		print_dup2_error(void);
int		is_there_path_in_env(char **env);
int		get_exit_status_and_print(char *path, char **env);
int		check_is_a_directory(char *path);
int		setting_up_redirections(t_command *cmd, t_shell *shell);
int		check_digits_and_skip_spaces(char *arg, int i);
int		handle_fork_error(pid_t pid, t_shell *shell);

//built_in
void	print_export(t_envir **env_array, int env_list_count);
void	read_new_path_and_update_old_path(t_envir **env, char *old_path);
void	print_for_echo_arg(char **arg, int start_print, int is_there_n_flag);
void	exit_cmd(char **array_of_arg, t_shell *shell);
char	*allocate_and_fill_key(char *env_line);
char	*get_key_value_from_env(t_envir *env, char *key);
int		env_cmd(t_envir *env, char **arg);
int		pwd_cmd(void);
int		sort_env(t_envir *env);
int		export_cmd(char **arg, t_envir **env);
int		echo_cmd(char **array_of_arg);
int		handle_cd_without_args(t_envir **env, char *old_path);
int		cd_cmd(t_envir **env, char **arg);
int		unset_cmd(t_envir **env, char **arg);
int		check_flag(char **array_of_arg);
int		get_value_and_key(char *env_line, t_envir **the_start_node);
int		check_export_key_validation(char *the_key);
int		is_cmd_built_in(char *cmd);
int		built_in_controller(t_command *cmd, t_shell *shell);

#endif
