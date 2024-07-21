/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:59:54 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/21 14:17:17 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/parser.h"

extern t_sig	g_sig;

char	*set_prompt(char *input)
{
	char	*prompt;

	if (input == NULL)
		return (NULL);
	prompt = malloc(strlen(input) + 1);
	if (prompt == NULL)
	{
		printf("Error: malloc failed\n");
		exit(1);
	}
	strcpy(prompt, input);
	return (prompt);
}

int	is_only_whitespace(const char *str)
{
	while (*str)
	{
		if (!isspace((unsigned char)*str))
			return (0);
		str++;
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	char		*prompt;
	char		*input;
	t_lexer		lexer;
	t_parser	*parser;
	t_cmd_node	*cmd;
	t_env		envp;

	cmd = NULL;
	(void)argv;
	(void)argc;
	init_env(&envp, env);
	prompt = set_prompt("balkanshell$ ");
	while (1)
	{
		input = readline(prompt);
		if (input == NULL || *input == '\0' || is_only_whitespace(input))
		{
			free(input);
			continue ;
		}
		init_lexer(&lexer, input);
		parser = init_parser(&lexer);
		parse_command(parser, &cmd, &envp);
		free_cmd_list(cmd);
		cmd = NULL;
		free(input);
	}
	free(prompt);
}
