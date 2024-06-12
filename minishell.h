/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:01:22 by dslaveev          #+#    #+#             */
/*   Updated: 2024/06/12 10:06:04 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include "lexer.h"

# define MAXARGS 10

enum cmd_types{
	PIPE = 1,
	LIST = 2,
	BACK = 3,
	EXEC = 4,
	REDIR = 5
};

struct s_cmd
{
	enum cmd_types	type;
	char			*cmd;
	char			**args;
}					t_cmd;

struct exec_cmd
{
	enum cmd_types type;
	char *argv[MAXARGS];
	char *eargv[MAXARGS];
};

struct pipe_cmd
{
	enum cmd_types type;
	struct cmd *left;
	struct cmd *right;
};

struct list_cmd
{
	enum cmd_types type;
	struct cmd *left;
	struct cmd *right;
};

struct redir_cmd
{
	enum cmd_types type;
	struct cmd *cmd;
	char *start_f;
	char *end_f;
	int mode;
	int fd;
};

struct back_cmd
{
	enum cmd_types type;
	struct cmd *cmd;
};

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
