/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:50:57 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/21 15:10:24 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_command_in_path(char *command, t_env *env)
{
	t_env_var	*current;
	char		*path;
	char		*path_env;
	char		*result;

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
	if (path == NULL)
		ft_error("Failed to allocate memory", 1);
	result = search_command_in_path(path, command);
	free(path);
	return (result);
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

void	open_input_file(t_cmd *cmd, t_fds *fds)
{
	if (cmd->fd_in)
	{
		fds->fd_input = open(cmd->fd_in, O_RDONLY);
		if (fds->fd_input == -1)
			ft_error("Failed to open input file", 1);
	}
}

void	handle_pipe_creation(t_cmd *cmd, t_fds *fds)
{
	if (cmd->pipe && pipe(fds->pipe_fd) == -1)
		ft_error("Failed to create pipe", 1);
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
