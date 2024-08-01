/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:57:02 by jsamardz          #+#    #+#             */
/*   Updated: 2024/07/31 15:20:57 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	help_eof(char *input)
{
	if (!input)
		handle_eof();
}

void	destroy_token(t_tok *token)
{
	free(token->value);
	free(token);
}

void	ft_check(char **environ)
{
	if (environ == NULL)
		return ;
}

void	cleanup_shell(t_env *env)
{
	free_env(env);
}

void	ft_value(char *value)
{
	if (!value)
	{
		perror("malloc");
		exit(1);
	}
}
