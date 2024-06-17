/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 14:00:20 by dslaveev          #+#    #+#             */
/*   Updated: 2024/04/03 18:19:04 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_read_line_fd(int fd, char **charcters_left, char *buffer);
static char	*get_line(char **line_buff);

char	*get_next_line(int fd)
{
	static char	*charcters_left;
	char		*lstr;
	char		*buffer;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	lstr = ft_read_line_fd(fd, &charcters_left, buffer);
	if (lstr == NULL)
	{
		return (free(buffer), free(lstr), NULL);
	}
	free(buffer);
	return (lstr);
}

/// @brief The line_buffer function reads from the file
/// descriptor and appends the characters to
/// charcters_left until a newline character is found
/// or the end of the file is reached.
/// @param fd
/// @param charcters_left
/// @param buffer
static char	*ft_read_line_fd(int fd, char **charcters_left, char *buffer)
{
	ssize_t	bytes_used;
	char	*tmp;

	bytes_used = 1;
	while (bytes_used > 0)
	{
		bytes_used = read(fd, buffer, BUFFER_SIZE);
		if (bytes_used <= 0)
			break ;
		if (*charcters_left == NULL)
			*charcters_left = ft_strdup("");
		buffer[bytes_used] = 0;
		tmp = ft_strjoin(*charcters_left, buffer);
		free(*charcters_left);
		*charcters_left = tmp;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (bytes_used == -1)
	{
		return (free(*charcters_left), *charcters_left = NULL, NULL);
	}
	return (get_line(charcters_left));
}

/// @brief The get_line function extracts a line from charcters_left
/// and updates charcters_left to contain any remaining characters.
/// @param line_buff
static char	*get_line(char **line_buff)
{
	char	*charcters_left;
	char	*extract_line;
	size_t	i;

	i = 0;
	if (*line_buff == NULL)
		return (NULL);
	while ((*line_buff)[i] != '\0' && (*line_buff)[i] != '\n')
		i++;
	if ((*line_buff)[i] == '\n')
		i++;
	extract_line = ft_substr(*line_buff, 0, i);
	charcters_left = ft_strdup(*line_buff + i);
	free(*line_buff);
	*line_buff = charcters_left;
	if (**line_buff == '\0')
	{
		free(*line_buff);
		*line_buff = NULL;
	}
	return (extract_line);
}
// int main(void)
// {
//     char	*line;
// 	int		i;
// 	int		fd1;

// 	fd1 = open("tst.txt", O_RDONLY);

// 	i = 1;
// 	while (i < 6)
// 	{
// 		line = get_next_line(fd1);
// 		printf("line [%01d]: %s", i, line);
// 		free(line);
// 		i++;
// 	}
// 	system("leaks a.out");
// 	close(fd1);
// 	return (0);
// }
