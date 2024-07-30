/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:49:40 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/30 14:36:47 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"
#include "../../libft/libft.h"

int	open_heredoc_file(char *tempfile)
{
	int	fd;

	fd = open(tempfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_error("Failed to open heredoc file", 1);
	return (fd);
}

void	write_line_to_file(int fd, char *line, size_t line_len)
{
	write(fd, line, line_len);
	write(fd, "\n", 1);
}

char	*prompt_and_read_line(char *delimiter)
{
	char	*line;
	size_t	line_len;

	write(1, "> ", 2);
	line = get_next_line(0);
	line_len = ft_strlen(line);
	if (line[line_len - 1] == '\n')
	{
		line[line_len - 1] = '\0';
	}
	if (!ft_strcmp(line, delimiter))
	{
		free(line);
		return (NULL);
	}
	return (line);
}

void	handle_heredoc(t_cmd *cmd)
{
	char	*delimiter;
	int		fd;
	char	*tempfile;
	char	*line;

	tempfile = "/tmp/minishell_heredoc";
	if (!cmd->heredock)
		return ;
	delimiter = cmd->fd_heredoc;
	if (!delimiter)
		return ;
	fd = open_heredoc_file(tempfile);
	while (true)
	{
		line = prompt_and_read_line(delimiter);
		if (!line)
			break ;
		write_line_to_file(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	cmd->fd_in = ft_strdup(tempfile);
}

bool	heredoc_check(t_parser *parser, t_cmd *cmd)
{
	cmd->heredock = false;
	if (parser->current_token->type == CHAR_LESS)
	{
		parser_advance(parser);
		if (parser->current_token->type == CHAR_LESS)
			cmd->heredock = true;
	}
	return (cmd->heredock);
}
