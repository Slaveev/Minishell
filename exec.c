/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:41:17 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/18 13:50:06 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

char	*find_command_in_path(char *command, t_env *env)
{
	t_env_var	*current;
	char		*path;
	char		*path_env;
	char		*token;
	char		full_path[1024];

	path_env = NULL;
	current = env->vars;
	while (current != NULL)
	{
		if (strncmp(current->key, "PATH", 4) == 0 && current->key[4] == '\0')
		{
			path_env = current->value;
			break ;
		}
		current = current->next;
	}
	if (path_env == NULL)
		return (NULL);
	path = strdup(path_env);
	token = strtok(path, ":");
	while (token != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", token, command);
		if (access(full_path, X_OK) == 0)
			return (free(path), strdup(full_path));
		token = strtok(NULL, ":");
	}
	free(path);
	return (NULL);
}

void	handle_heredoc(t_cmd *cmd)
{
	char	*delimeter;
	int		fd;
	size_t	line_len;
	char	*tempfile;
	char	*line;

	line = NULL;
	delimeter = NULL;
	if (cmd->heredock)
		delimeter = cmd->fd_heredoc;
	if (!delimeter)
		return ;
	tempfile = "/tmp/minishell_heredoc";
	fd = open(tempfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_error("Failed to open heredoc file", 1);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		line_len = strlen(line);
		if (line[line_len - 1] == '\n')
		{
			line[line_len - 1] = '\0';
			line_len--;
		}
		if (strcmp(line, delimeter) == 0)
		{
			free(line);
			line = NULL;
			break ;
		}
		write(fd, line, line_len);
		write(fd, "\n", 1);
		free(line);
		line = NULL;
	}
	close(fd);
	cmd->fd_in = strdup(tempfile);
}

void	open_input_file(t_cmd *cmd, t_fds *fds)
{
	if (cmd->fd_in)
	{
		fds->fd_input = open(cmd->fd_in, O_RDONLY);
		if (fds->fd_input == -1)
			ft_error("Failed to open input file", 1);
	}
}

void	handle_redirections(t_exec_context *context)
{
	if (context->fds.fd_input != -1
		&& dup2(context->fds.fd_input, STDIN_FILENO) == -1)
		ft_error("Failed to redirect stdin", 1);
	if (context->fds.fd_output != -1
		&& dup2(context->fds.fd_output, STDOUT_FILENO) == -1)
		ft_error("Failed to redirect stdout", 1);
	if (context->cmd->pipe)
	{
		close(context->fds.pipe_fd[0]);
		if (dup2(context->fds.pipe_fd[1], STDOUT_FILENO) == -1)
			ft_error("Failed to redirect stdout to pipe", 1);
	}
}

void	open_output_file(t_cmd *cmd, t_fds *fds)
{
	int	flag;

	if (cmd->fd_out)
	{
		if (cmd->fd_append)
			flag = O_WRONLY | O_CREAT | O_APPEND;
		else
			flag = O_WRONLY | O_CREAT | O_TRUNC;
		fds->fd_output = open(cmd->fd_out, flag, 0644);
		if (fds->fd_output == -1)
			ft_error("Failed to open output file", 1);
	}
}

void	handle_pipe_creation(t_cmd *cmd, t_fds *fds)
{
	if (cmd->pipe && pipe(fds->pipe_fd) == -1)
		ft_error("Failed to create pipe", 1);
}

void	execute_builtin_command(t_cmd *cmd, t_env *env, t_fds *fds)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = -1;
	saved_stdout = -1;
	if (fds->fd_input != -1)
	{
		saved_stdin = dup(STDIN_FILENO);
		if (dup2(fds->fd_input, STDIN_FILENO) == -1)
			ft_error("Failed to redirect stdin", 1);
	}
	if (fds->fd_output != -1)
	{
		saved_stdout = dup(STDOUT_FILENO);
		if (dup2(fds->fd_output, STDOUT_FILENO) == -1)
			ft_error("Failed to redirect stdout", 1);
	}
	builtin_exec(cmd->args, env);
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
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
		ft_error("Command not found", 127);
	envp = env_to_char_array(context->env);
	if (execve(cmd_path, context->cmd->args, envp) == -1)
		ft_error("Command not executable", 126);
	free_char_array(envp);
}

void	cleanup(t_fds *fds, pid_t pid, int *cmd_status)
{
	if (fds->fd_input != -1)
		close(fds->fd_input);
	if (fds->fd_output != -1)
		close(fds->fd_output);
	if (fds->pipe_fd[0] != -1)
		close(fds->pipe_fd[1]);
	waitpid(pid, cmd_status, 0);
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
