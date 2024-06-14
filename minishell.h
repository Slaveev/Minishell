/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:01:22 by dslaveev          #+#    #+#             */
/*   Updated: 2024/06/14 13:21:44 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include "lexer.h"
# include "parser.h"
# include "builtin.h"

# define MAXARGS 10

enum e_cmd_types{
	PIPE = 1,
	LIST = 2,
	BACK = 3,
	EXEC = 4,
	REDIR = 5
};

struct s_cmd
{
	enum e_cmd_types	type;
	char				*cmd;
	char				**args;
	struct s_cmd		*left;
	struct s_cmd		*right;
}						t_cmd;

struct s_exec_cmd
{
	enum e_cmd_types	type;
	char				*argv[MAXARGS];
	char				*eargv[MAXARGS];
};

struct s_pipe_cmd
{
	enum e_cmd_types	type;
	struct s_cmd		*left;
	struct s_cmd		*right;
};

struct s_list_cmd
{
	enum e_cmd_types	type;
	struct s_cmd		*left;
	struct s_cmd		*right;
};

struct s_redir_cmd
{
	enum e_cmd_types	type;
	struct s_cmd		*cmd;
	char				*start_f;
	char				*end_f;
	int					mode;
	int					fd;
};

struct s_back_cmd
{
	enum e_cmd_types	type;
	struct s_cmd		*cmd;
};

typedef struct s_arg
{
	char			*value;
	struct s_arg	*next;
}					t_arg;

void	execute_command(char *command, char **args);
void	builtin_exec(char **input, char **env);

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
