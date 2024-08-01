/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD:utils.c
/*   By: jsamardz <jsamardz@student.42heilnronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:42:14 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/01 12:44:34 by jsamardz         ###   ########.fr       */
=======
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:42:14 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/30 14:39:31 by jsamardz         ###   ########.fr       */
>>>>>>> workbulgaria:srcs/utils/utils.c
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
	if (ft_strcmp(command, "cd") == 0
		|| ft_strcmp(command, "pwd") == 0
		|| ft_strcmp(command, "echo") == 0
		|| ft_strcmp(command, "exit") == 0
		|| ft_strcmp(command, "env") == 0
		|| ft_strcmp(command, "export") == 0
		|| ft_strcmp(command, "unset") == 0)
	{
		return (1);
	}
	return (0);
}

// void	ft_error(char *msg, int e)
// {
// 	fprintf(stderr, "Error: %s", msg);
// 	exit(EXIT_FAILURE);
// }
