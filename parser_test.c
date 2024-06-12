/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 10:02:25 by dslaveev          #+#    #+#             */
/*   Updated: 2024/06/12 11:58:15 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(void)
{
	struct exec_cmd *cmd;

	cmd = malloc(sizeof(struct exec_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->type = EXEC;
	return (struct cmd *)cmd;
}

struct s_cmd	*create_cmd(enum cmd_types type, char *cmd, char **args)
{
	struct s_cmd	*new_cmd;

	new_cmd = malloc(sizeof(struct s_cmd));
	if (new_cmd == NULL)
		return (NULL);
	new_cmd->type = type;
	new_cmd->cmd = strdup(cmd);
	new_cmd->args = args;
	return (new_cmd);
}
