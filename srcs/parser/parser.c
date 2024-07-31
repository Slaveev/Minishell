/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:07:17 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/31 14:37:04 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
#include "../../libft/libft.h"

void	init_cmd_and_arg(t_parser *parser, t_cmd *current_cmd,
		t_cmd_node **cmd_list, int flag)
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
	flag = parser->current_token->flag;
}

int	add_together(t_parser *parser, t_cmd *current_cmd,
		t_cmd_node **cmd_list)
{
	int		args_len;
	char	**resulted_args;
	int		flag;

	flag = 0;
	args_len = 0;
	while (current_cmd->args[args_len] != NULL)
		++args_len;
	resulted_args = realloc(current_cmd->args, sizeof(char *) * (args_len + 2));
	if (resulted_args == NULL)
	{
		perror("Failed to reallocate memory for args");
		free_cmd_list(*cmd_list);
		return (0);
	}
	current_cmd->args = resulted_args;
	current_cmd->args[args_len] = ft_strdup(parser->current_token->value);
	if (current_cmd->args[args_len] == NULL)
	{
		perror("Failed to duplicate argument string");
		free_cmd_list(*cmd_list);
		return (0);
	}
	current_cmd->args[args_len + 1] = NULL;
	flag = parser->current_token->flag;
	return (flag);
}

int	handle_command_and_args(t_parser *parser, t_cmd *current_cmd,
		t_cmd_node **cmd_list)
{
	int	flag = 0;

	if (current_cmd->command == NULL)
	{
		init_cmd_and_arg(parser, current_cmd, cmd_list, flag);
	}
	else
	{
		flag = add_together(parser, current_cmd, cmd_list);
	}
	return (flag);
}

void	proccess_command(t_parser *parser, t_manager *cmd_mgmt, t_env *env)
{
	int		cmd_flag;
	char	**envp;
	int		flag;

	flag = 0;
	cmd_flag = 1;
	flag = process_tokens(parser, cmd_mgmt, &cmd_flag);

	envp = env_to_char_array(env);
	ft_execute(*(cmd_mgmt->cmd_list), env, flag);
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
