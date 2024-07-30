/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:12:03 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/30 13:05:16 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i] != NULL)
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

void	free_cmd_args(char **args)
{
	int	i;

	i = 0;
	if (args == NULL)
		return ;
	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd->command)
		free(cmd->command);
	if (cmd->args)
		free(cmd->args);
	free(cmd);
}

void	free_cmd_list(t_cmd_node *cmd_list)
{
	t_cmd_node	*tmp;

	while (cmd_list != NULL)
	{
		tmp = cmd_list;
		cmd_list = cmd_list->next;
		free_cmd_args(tmp->cmd->args);
		free(tmp->cmd);
		free(tmp);
	}
}

void	free_char_array(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i] != NULL)
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}
