/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 13:58:18 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/21 14:33:41 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	handle_heredoc(t_cmd *cmd)
// {
// 	char	*delimeter;
// 	int		fd;
// 	size_t	line_len;
// 	char	*tempfile;
// 	char	*line;

// 	line = NULL;
// 	delimeter = NULL;
// 	if (cmd->heredock)
// 		delimeter = cmd->fd_heredoc;
// 	if (!delimeter)
// 		return ;
// 	tempfile = "/tmp/minishell_heredoc";
// 	fd = open(tempfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	if (fd == -1)
// 		ft_error("Failed to open heredoc file", 1);
// 	while (1)
// 	{
// 		write(1, "> ", 2);
// 		line = get_next_line(0);
// 		line_len = strlen(line);
// 		if (line[line_len - 1] == '\n')
// 		{
// 			line[line_len - 1] = '\0';
// 			line_len--;
// 		}
// 		if (strcmp(line, delimeter) == 0)
// 		{
// 			free(line);
// 			line = NULL;
// 			break ;
// 		}
// 		write(fd, line, line_len);
// 		write(fd, "\n", 1);
// 		free(line);
// 		line = NULL;
// 	}
// 	close(fd);
// 	cmd->fd_in = strdup(tempfile);
// }

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
