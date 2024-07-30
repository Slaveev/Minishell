/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:36:52 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/30 14:30:17 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/parser.h"

int	count_env_vars(t_env_var *vars)
{
	int	count;

	count = 0;
	while (vars != NULL)
	{
		count++;
		vars = vars->next;
	}
	return (count);
}

char	**allocate_env_array(int count)
{
	char	**envp;

	envp = malloc(sizeof(char *) * (count + 1));
	if (envp == NULL)
	{
		perror("malloc failed");
		exit(1);
	}
	return (envp);
}

void	fill_env_array(char **envp, t_env_var *vars)
{
	int		i;
	size_t	len;

	i = 0;
	while (vars != NULL)
	{
		len = ft_strlen(vars->key) + ft_strlen(vars->value) + 2;
		envp[i] = malloc(len);
		if (envp[i] == NULL)
		{
			perror("malloc failed");
			exit(1);
		}
		strcpy(envp[i], vars->key);
		strcat(envp[i], "=");
		strcat(envp[i], vars->value);
		vars = vars->next;
		i++;
	}
	envp[i] = NULL;
}

char	**env_to_char_array(t_env *env)
{
	int		count;
	char	**envp;

	count = count_env_vars(env->vars);
	envp = allocate_env_array(count);
	fill_env_array(envp, env->vars);
	return (envp);
}
