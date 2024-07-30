/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:58:18 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/30 14:39:11 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	redirect_and_close(int oldfd, int newfd)
{
	int	saved_fd;

	if (oldfd != -1)
	{
		saved_fd = dup(newfd);
		if (dup2(oldfd, newfd) == -1)
			ft_error("Failed to redirect file descriptor", 1);
		close(saved_fd);
	}
}

void	restore_fd(int saved_fd, int target_fd)
{
	if (saved_fd != -1)
	{
		if (dup2(saved_fd, target_fd) == -1)
			ft_error("Failed to restore file descriptor", 1);
		close(saved_fd);
	}
}
