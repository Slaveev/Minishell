/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:17:28 by jsamardz          #+#    #+#             */
/*   Updated: 2024/07/30 13:05:26 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env(t_env *env)
{
	t_env_var	*current;
	t_env_var	*next;

	current = env->vars;
	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	free(env->curr_dir);
}

void	free_env_vars(t_env *env)
{
	t_env_var	*current;
	t_env_var	*next;

	current = env->vars;
	while (current != NULL)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	env->vars = NULL;
	if (env->curr_dir != NULL)
	{
		free(env->curr_dir);
		env->curr_dir = NULL;
	}
}

void	free_lexer(t_lexer *lexer)
{
	if (lexer != NULL)
	{
		free(lexer->input);
		free(lexer);
	}
}

void	free_token(t_tok *token)
{
	if (token != NULL)
	{
		free(token->value);
		free(token);
	}
}

void	ftcleanup(t_shell_env *shell)
{
	free_env_vars(&shell->env);
	clear_history();
}
