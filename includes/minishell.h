/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:14:25 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/24 15:27:20 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "../includes/lexer.h"
// # include "../in"
# include "builtin.h"
# include <signal.h>
# include <stdbool.h>

# define MAXARGS 10

enum e_cmd_types{
	PIPE = 1,
	LIST = 2,
	BACK = 3,
	EXEC = 4,
	REDIR = 5
};

typedef struct s_sig
{
	int	status;
}		t_sig;

extern t_sig	g_sig;

typedef struct s_cmd
{
	char			*command;
	char			**args;
	char			*fd_in;
	char			*fd_out;
	char			*fd_heredoc;
	bool			fd_append;
	bool			heredock;
	pid_t			pid;
	bool			pipe;
	int				status;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_cmd_node
{
	t_cmd				*cmd;
	struct s_cmd_node	*next;
}						t_cmd_node;

typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}						t_env_var;

typedef struct s_env
{
	t_env_var	*vars;
	char		*curr_dir;
}				t_env;

typedef struct s_fds
{
	int	fd_input;
	int	fd_output;
	int	pipe_fd[2];
}		t_fds;

typedef struct s_exec_context
{
	t_cmd	*cmd;
	t_env	*env;
	t_fds	fds;
}			t_exec_context;

typedef struct s_shell_env
{
	t_env		env;
	t_lexer		lexer;
	t_cmd_node	*cmd;
}				t_shell_env;

char	*expander_env(char *arg, char **env);
int		builtin_exec(char **input, t_env *env);
void	print_token(t_tok *token);
void	ft_execute(t_cmd_node *cmd_list, t_env *env);
void	free_cmd_list(t_cmd_node *cmd_list);
int		is_builtin(char *command);
void	ft_error(const char *msg, int status);
void	free_char_array(char **array);
char	**env_to_char_array(t_env *env);

void	handle_env(t_env *env);
void	handle_cd(char **input, t_env *env);

void	init_env(t_env *env, char **environ);
void	set_env_var(t_env *env, const char *key, const char *value);
void	unset_env_var(t_env *env, const char *key);
char	*get_env_var(t_env *env, const char *key);
void	change_dir_exec(t_env *env, const char *path);
void	free_env(t_env *env);

char	*find_command_in_path(char *command, t_env *env);
void	open_output_file(t_cmd *cmd, t_fds *fds);
void	open_input_file(t_cmd *cmd, t_fds *fds);
void	handle_pipe_creation(t_cmd *cmd, t_fds *fds);
void	cleanup(t_fds *fds, pid_t pid, int *cmd_status);

void	handle_redirections(t_exec_context *context);
void	handle_heredoc(t_cmd *cmd);
void	redirect_and_close(int oldfd, int newfd);
void	restore_fd(int saved_fd, int target_fd);

int		open_heredoc_file(char *tempfile);
void	write_line_to_file(int fd, char *line, size_t line_len);
char	*prompt_and_read_line(char *delimiter);
void	handle_heredoc(t_cmd *cmd);

void	free_env(t_env *env);
int		is_only_whitespace(const char *str);

char	*search_command_in_path(char *path, char *command);

#endif
