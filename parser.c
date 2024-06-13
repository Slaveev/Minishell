/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:07:17 by dslaveev          #+#    #+#             */
/*   Updated: 2024/06/13 13:25:16 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_parser	*init_parser(t_lexer *lexer)
{
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
	if (parser == NULL)
		return (NULL);
	parser->lexer = lexer;
	parser->current_token = lexer_get_next_token(lexer);
	return (parser);
}

void	parser_advance(t_parser *parser)
{
	parser->current_token = lexer_get_next_token(parser->lexer);
}

int	is_builtin(char *command)
{
	char	*builtins[] = {"cd", "pwd", "echo", "exit", "env", "export", "unset"};
	int		i;
	int		num_builtins;

	i = 0;
	num_builtins = sizeof(builtins) / sizeof(char *);
	while (i < num_builtins)
	{
		if (!strcmp(command, builtins[i]))
			return (1);
		i++;
	}
	return (0);
}

void	handle_command(char *command, char **args, t_parser *parser, int *i)
{
	args[(*i)++] = command;
	if (is_builtin(command))
	{
		args[*i] = NULL;
		builtin_exec(parser->lexer->input, args);
	}
}

void	handle_argument(char *arg, char **args, int *i)
{
	args[(*i)++] = arg;
}

void	parse_command(t_parser *parser)
{
	char	*args[1024];
	int		i;
	int		command;

	command = 1;
	i = 0;
	while (parser->current_token != NULL)
	{
		if (parser->current_token->type == WORD && command)
		{
			printf("Command: %s\n", parser->current_token->value);
			handle_command(parser->current_token->value, args, parser, &i);
			command = 0;
		}
		else if (!command)
			handle_argument(parser->current_token->value, args, &i);
		if (parser->current_token->type == CHAR_PIPE)
		{
			printf("Pipe\n");
			command = 1;
		}
		parser_advance(parser);
	}
	args[i] = NULL;
	execute_command(args[0], args);
}

void	parse(t_parser *parser)
{
	parse_command(parser);
}
