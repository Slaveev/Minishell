/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:07:17 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/29 15:56:43 by dslaveev         ###   ########.fr       */
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
	current_cmd->args = calloc(2, sizeof(char *));
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
	while (parser->current_token != NULL)
	{
		if (cmd_flag == 1)
			initialize_cmd_node(parser, cmd_mgmt, &cmd_flag);
		if (parser->current_token->type == CHAR_PIPE)
			handle_pipe(*(cmd_mgmt->current_cmd), &cmd_flag);
		else if (parser->current_token->type == CHAR_MORE
			|| parser->current_token->type == CHAR_DOUBLE_MORE)
			handle_output_redirection(parser, *(cmd_mgmt->current_cmd),
				cmd_mgmt->cmd_list);
		else if (parser->current_token->type == CHAR_LESS)
		{
			printf("input\n");
			handle_input_redirection(parser, *(cmd_mgmt->current_cmd),
				cmd_mgmt->cmd_list);
		}
		else if (parser->current_token->type == WORD)
			handle_command_and_args(parser, *(cmd_mgmt->current_cmd),
				cmd_mgmt->cmd_list);
		parser_advance(parser);
		printf("seg\n");
	}
	envp = env_to_char_array(env);
	ft_execute(*(cmd_mgmt->cmd_list), env);
	free_2d_array(envp);
	printf("freed\n");
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
