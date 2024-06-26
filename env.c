/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 13:15:17 by dslaveev          #+#    #+#             */
/*   Updated: 2024/06/26 13:22:29 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_env *env, char **environ)
{
	int i;
	char *key;
	char *value;

	env->vars = NULL;
	env->curr_dir = NULL;
	i = 0;
	while (environ[i] != NULL)
	{
		key = ft_split(environ[i], '=');
		value = ft_split(NULL, "");
		set_env_var(env, key, value);
		if (!ft_strcmp(key, "PWD"))
			env->curr_dir = ft_strdup(value);
		i++;
	}
}

void	set_env_var(t_env *env, const char *key, const char *value)
{
	t_env *current;

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
	t_env_var *new_var = malloc(sizeof(t_env_var));
	if (new_var == NULL)
	{
		printf("Error: malloc failed\n");
		exit(1);
	}
	new_var->key = ft_strdup(key);
	new_var->value = ft_strdup(value);
	new_var->next = env->vars;
	env->vars = new_var;
}
