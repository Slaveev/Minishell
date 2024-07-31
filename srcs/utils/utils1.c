/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 14:43:19 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/31 15:19:57 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

int	is_only_whitespace(const char *str)
{
	while (*str)
	{
		if (!isspace((unsigned char)*str))
			return (0);
		str++;
	}
	return (1);
}

char	*search_command_in_path(char *path, char *command)
{
	char	full_path[1024];
	char	*token;

	token = strtok(path, ":");
	while (token != NULL)
	{
		snprintf(full_path, sizeof(full_path), "%s/%s", token, command);
		if (access(full_path, X_OK) == 0)
			return (ft_strdup(full_path));
		token = strtok(NULL, ":");
	}
	return (NULL);
}

char	*strip_single_quotes(char *str)
{
	int	i;

	i = ft_strlen(str);
	if (str[0] == '\'' && str[i - 1] == '\'')
	{
		str[i - 1] = '\0';
		return (str + 1);
	}
	return (str);
}

void	helper(char *arg, char *key)
{
	key = getenv(arg + 1);
	if (key)
		printf("%s", key);
	else
		printf("%s", arg);
}

void	helper2(char *key, char *value)
{
	helper(value, key);
	free(value);
}
