/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:32:56 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/31 13:54:58 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"
#include "../../includes/minishell.h"
#include "../../includes/parser.h"

void	print_env_vars(t_env *env)
{
	t_env_var	*current;

	current = env->vars;
	while (current != NULL)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

void	handle_export(char **input, t_env *env)
{
	char	*key;
	char	*value;

	if (input[1] == NULL)
		print_env_vars(env);
	else
	{
		key = input[1];
		if (input[2] != NULL && input[2][0] == '=')
			value = &input[2][1];
		else
			value = "";
		if (key && value)
			set_env_var(env, key, value);
	}
	g_sig.status = 0;
}

void	handle_unset(char **input, t_env *env)
{
	if (input[1] != NULL)
		unset_env_var(env, input[1]);
	g_sig.status = 0;
}

void	handle_cd(char **input, t_env *env)
{
	char	*home;

	if (input[1] == NULL)
	{
		home = get_env_var(env, "HOME");
		if (home)
			change_dir_exec(env, home);
		else
			printf("cd: HOME not set\n");
	}
	else
		change_dir_exec(env, input[1]);
	g_sig.status = 0;
}

int	builtin_exec(char **input, t_env *env, int flag)
{
	if (!ft_strncmp(input[0], "env", 4))
	{
		print_env_vars(env);
		g_sig.status = 0;
	}
	else if (!ft_strncmp(input[0], "exit", 4))
		exit_status(input);
	else if (!ft_strncmp(input[0], "echo", 4))
		handle_echo(input, flag);
	else if (!ft_strncmp(input[0], "pwd", 3) && input[1] == NULL)
		handle_pwd();
	else if (!ft_strncmp(input[0], "cd", 2))
		handle_cd(input, env);
	else if (!ft_strncmp(input[0], "export", 6))
		handle_export(input, env);
	else if (!ft_strncmp(input[0], "unset", 5))
		handle_unset(input, env);
	return (g_sig.status);
}
