/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilnronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 13:14:25 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/01 12:43:56 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include "libft/libft.h"
# include "lexer.h"
// # include "parser.h"
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
	int		sigint;
	int		sigquit;
	int		exstatus;
	pid_t	pid;
}				t_sig;

typedef struct s_cmd
{
	char			*command;
	char			**args;
	char			*fd_in;
	char			*fd_out;
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
	char *key;
	char *value;
	struct s_env_var *next;
}	t_env_var;

typedef struct s_env
{
	t_env_var *vars;
	char *curr_dir;
} t_env;

char	*expander_env(char *arg, char **env);
void	builtin_exec(char **input, char **env);
void	print_token(t_tok *token);
void free_cmd_list(t_cmd_node *cmd_list);
void ft_execute(t_cmd_node *cmd_list, char **env);
void	signal_setup();

#endif

// parsecmd
//	parsepipe
//	parseredir
//	parseback
//	parseexec
// 	parsebllock
// nullterminate
// gettoken

// main
// getcmd
// runcmd
// panic
// fork1
