/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:57:02 by jsamardz          #+#    #+#             */
/*   Updated: 2024/07/30 13:20:16 by jsamardz         ###   ########.fr       */
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
