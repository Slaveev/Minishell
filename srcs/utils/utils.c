/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:42:14 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/21 14:32:26 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_close_fd(int *pfd)
{
	close(pfd[0]);
	close(pfd[1]);
}

void	ft_error(const char *msg, int status)
{
	perror(msg);
	exit(status);
}

void	free_str_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*get_cmd_path(char *cmd, char **env)
{
	int		i;
	char	**paths;
	char	*path;
	char	*tmp;

	i = 0;
	if (env == NULL)
		return (NULL);
	while (env[i] != NULL && ft_strncmp(env[i], "PATH=", 5))
		i++;
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, X_OK | F_OK) == 0)
			return (free_str_array(paths), path);
		free(path);
		i++;
	}
	return (free_str_array(paths), NULL);
}

int	is_builtin(char *command)
{
	if (command == NULL)
		return (0);
	if (strcmp(command, "cd") == 0
		|| strcmp(command, "pwd") == 0
		|| strcmp(command, "echo") == 0
		|| strcmp(command, "exit") == 0
		|| strcmp(command, "env") == 0
		|| strcmp(command, "export") == 0
		|| strcmp(command, "unset") == 0)
	{
		printf("builtin\n");
		return (1);
	}
	return (0);
}
