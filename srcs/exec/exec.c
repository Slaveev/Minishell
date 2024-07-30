/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:41:17 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/30 23:12:39 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

void	execute_builtin_command(t_cmd *cmd, t_env *env, t_fds *fds)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = -1;
	saved_stdout = -1;
	if (fds->fd_input != -1)
	{
		saved_stdin = dup(STDIN_FILENO);
		redirect_and_close(fds->fd_input, STDIN_FILENO);
	}
	if (fds->fd_output != -1)
	{
		saved_stdout = dup(STDOUT_FILENO);
		redirect_and_close(fds->fd_output, STDOUT_FILENO);
	}
	g_sig.status = builtin_exec(cmd->args, env);
	restore_fd(saved_stdin, STDIN_FILENO);
	restore_fd(saved_stdout, STDOUT_FILENO);
}

void	execute_command(t_exec_context *context)
{
	char	*cmd_path;
	char	**envp;

	cmd_path = NULL;
	if (context->cmd->command[0] == '/')
		cmd_path = context->cmd->command;
	else
		cmd_path = find_command_in_path(context->cmd->command, context->env);
	if (!cmd_path)
	{
		ft_error("Command not found", 127);
	}
	envp = env_to_char_array(context->env);
	if (execve(cmd_path, context->cmd->args, envp) == -1)
		ft_error("Command not executable", 126);
}

void	execute_external_command(t_exec_context *context)
{
	context->cmd->pid = fork();
	if (context->cmd->pid == 0)
	{
		handle_redirections(context);
		execute_command(context);
		exit(EXIT_FAILURE);
	}
	else
		cleanup(&context->fds, context->cmd->pid, &context->cmd->status);
}

void	ft_execute(t_cmd_node *cmd_list, t_env *env)
{
	t_cmd_node		*current_node;
	t_exec_context	context;

	current_node = cmd_list;
	while (current_node != NULL)
	{
		context.cmd = current_node->cmd;
		context.env = env;
		context.fds.fd_input = -1;
		context.fds.fd_output = -1;
		handle_heredoc(context.cmd);
		open_input_file(context.cmd, &context.fds);
		open_output_file(context.cmd, &context.fds);
		handle_pipe_creation(context.cmd, &context.fds);
		if (is_builtin(context.cmd->command))
			execute_builtin_command(context.cmd, env, &context.fds);
		else
			execute_external_command(&context);
		current_node = current_node->next;
	}
}
