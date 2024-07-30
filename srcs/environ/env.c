/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:15:17 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/30 14:30:52 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

void	init_env(t_env *env, char **environ)
{
	int		i;
	char	**splited;
	char	*key;
	char	*value;

	env->vars = NULL;
	env->curr_dir = NULL;
	i = -1;
	ft_check(environ);
	while (environ[++i] != NULL)
	{
		splited = ft_split(environ[i], '=');
		if (splited[0] && splited[1])
		{
			key = splited[0];
			value = splited[1];
			set_env_var(env, key, value);
			if (!ft_strcmp(key, "PWD"))
			{
				free(env->curr_dir);
				env->curr_dir = ft_strdup(value);
			}
		}
		free_2d_array(splited);
	}
}

void	set_env_var(t_env *env, const char *key, const char *value)
{
	t_env_var	*current;
	t_env_var	*new_var;

	current = env->vars;
	while (current != NULL)
	{
		if (!ft_strcmp(current->key, key))
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
	new_var = malloc(sizeof(t_env_var));
	if (new_var == NULL)
	{
		ft_putendl_fd("Error: malloc failed", 2);
		exit(1);
	}
	new_var->key = ft_strdup(key);
	new_var->value = ft_strdup(value);
	new_var->next = env->vars;
	env->vars = new_var;
}

void	unset_env_var(t_env *env, const char *key)
{
	t_env_var	**current;
	t_env_var	*delete_env;

	current = &env->vars;
	while (*current != NULL)
	{
		if (!ft_strcmp((*current)->key, key))
		{
			delete_env = *current;
			*current = (*current)->next;
			free(delete_env->key);
			free(delete_env->value);
			free(delete_env);
			return ;
		}
		current = &(*current)->next;
	}
}

char	*get_env_var(t_env *env, const char *key)
{
	t_env_var	*current;

	current = env->vars;
	while (current != NULL)
	{
		if (!ft_strcmp(current->key, key))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	change_dir_exec(t_env *env, const char *path)
{
	if (chdir(path) == 0)
	{
		free(env->curr_dir);
		env->curr_dir = getcwd(NULL, 0);
		if (env->curr_dir)
			set_env_var(env, "PWD", env->curr_dir);
		else
			perror("getcwd error: ");
	}
	else
		perror("chdir error: ");
}
