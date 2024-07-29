/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:12:03 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/29 15:49:43 by dslaveev         ###   ########.fr       */
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

void free_cmd_list(t_cmd_node *cmd_list) {
    t_cmd_node *tmp;

    while (cmd_list != NULL) {
        // free_2d_array(cmd_list->cmd->args); // Free the arguments of the command
        if (cmd_list->cmd->command != NULL) {
            free(cmd_list->cmd->command); // Free the command string if it's separately allocated
        }
        free(cmd_list->cmd); // Free the command structure itself
        tmp = cmd_list;
        cmd_list = cmd_list->next;
        free(tmp); // Free the node
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
