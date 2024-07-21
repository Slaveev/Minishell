/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:07:17 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/21 15:44:04 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	init_cmd_and_arg(t_parser *parser, t_cmd *current_cmd, t_cmd_node **cmd_list)
{
	current_cmd->command = strdup(parser->current_token->value);
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

void	add_together(t_parser *parser, t_cmd *current_cmd, t_cmd_node **cmd_list)
{
	int		args_len;
	char	**resulted_args;

	args_len = 0;
	while (current_cmd->args[args_len] != NULL)
		++args_len;
	resulted_args = realloc(current_cmd->args, sizeof(char*) * (args_len + 2));
	if (resulted_args == NULL)
	{
		perror("Failed to reallocate memory for args");
		free_cmd_list(*cmd_list);
		return ;
	}
	current_cmd->args = resulted_args;
	current_cmd->args[args_len] = strdup(parser->current_token->value);
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
		init_cmd_and_arg(parser, current_cmd, cmd_list);
	else
		add_together(parser, current_cmd, cmd_list);
}

void	parse_command(t_parser *parser, t_cmd_node **cmd_list, t_env *env)
{
	int			cmd_flag;
	t_cmd_node	*current_node;
	t_cmd		*current_cmd;
	char		**envp;

	cmd_flag = 1;
	current_node = NULL;
	current_cmd = NULL;
	while (parser->current_token != NULL)
	{
		if (cmd_flag == 1)
			initialize_cmd_node(parser, cmd_list, &current_node,
				&current_cmd, &cmd_flag);
		switch (parser->current_token->type)
		{
			case CHAR_PIPE:
				handle_pipe(current_cmd, &cmd_flag);
				break ;
			case CHAR_MORE:
			case CHAR_DOUBLE_MORE:
				handle_output_redirection(parser, current_cmd, cmd_list);
				break ;
			case CHAR_LESS:
				handle_input_redirection(parser, current_cmd, cmd_list);
				break ;
			case WORD:
				handle_command_and_args(parser, current_cmd, cmd_list);
				break ;
		}
		parser_advance(parser);
	}
	envp = env_to_char_array(env);
	ft_execute(*cmd_list, env);
	free_char_array(envp);
}
