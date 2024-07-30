/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:07:17 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/30 23:12:03 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../libft/libft.h"

void	init_cmd_and_arg(t_parser *parser, t_cmd *current_cmd,
		t_cmd_node **cmd_list)
{
	current_cmd->command = ft_strdup(parser->current_token->value);
	if (current_cmd->command == NULL)
	{
		perror("Failed to duplicate command string");
		free_cmd_list(*cmd_list);
		return ;
	}
	current_cmd->args = ft_calloc(2, sizeof(char *));
	if (current_cmd->args == NULL)
	{
		perror("Failed to allocate memory for args");
		free_cmd_list(*cmd_list);
		return ;
	}
	current_cmd->args[0] = current_cmd->command;
}

void	add_together(t_parser *parser, t_cmd *current_cmd,
		t_cmd_node **cmd_list)
{
	int		args_len;
	char	**resulted_args;

	args_len = 0;
	while (current_cmd->args[args_len] != NULL)
		++args_len;
	resulted_args = realloc(current_cmd->args, sizeof(char *) * (args_len + 2));
	if (resulted_args == NULL)
	{
		perror("Failed to reallocate memory for args");
		free_cmd_list(*cmd_list);
		return ;
	}
	current_cmd->args = resulted_args;
	current_cmd->args[args_len] = ft_strdup(parser->current_token->value);
	if (current_cmd->args[args_len] == NULL)
	{
		perror("Failed to duplicate argument string");
		free_cmd_list(*cmd_list);
		return ;
	}
	current_cmd->args[args_len + 1] = NULL;
}

void	handle_command_and_args(t_parser *parser, t_cmd *current_cmd,
		t_cmd_node **cmd_list)
{
	if (current_cmd->command == NULL)
	{
		init_cmd_and_arg(parser, current_cmd, cmd_list);
	}
	else
		add_together(parser, current_cmd, cmd_list);
}

void	proccess_command(t_parser *parser, t_manager *cmd_mgmt, t_env *env)
{
	int		cmd_flag;
	char	**envp;

	cmd_flag = 1;
	process_tokens(parser, cmd_mgmt, &cmd_flag);
	envp = env_to_char_array(env);
	ft_execute(*(cmd_mgmt->cmd_list), env);
	free_2d_array(envp);
}

void	parse_command(t_parser *parser, t_cmd_node **cmd_list, t_env *env)
{
	t_cmd_node	*current_node;
	t_cmd		*current_cmd;
	t_manager	cmd_mgmt;

	current_node = NULL;
	current_cmd = NULL;
	cmd_mgmt.cmd_list = cmd_list;
	cmd_mgmt.current_node = &current_node;
	cmd_mgmt.current_cmd = &current_cmd;
	proccess_command(parser, &cmd_mgmt, env);
}
