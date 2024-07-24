/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:59:54 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/24 15:06:29 by dslaveev         ###   ########.fr       */
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

int	process_input(char *input)
{
	if (input == NULL || *input == '\0' || is_only_whitespace(input))
	{
		free(input);
		return (0);
	}
	return (1);
}

void	leaks(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **env)
{
	char		*prompt;
	char		*input;
	t_shell_env	shell;
	t_parser	*parser;

	(void)argv;
	(void)argc;
	init_env(&shell.env, env);
	atexit(leaks);
	while (1)
	{
		prompt = set_prompt("balkanshell$ ");
		input = readline(prompt);
		free(prompt);
		if (!process_input(input))
			continue ;
		init_lexer(&shell.lexer, input);
		parser = init_parser(&shell.lexer);
		parse_command(parser, &shell.cmd, &shell.env);
		free_cmd_list(shell.cmd);
		shell.cmd = NULL;
		free(input);
	}
	free(prompt);
	free(input);
	free_char_array(env_to_char_array(&shell.env));
	free_env(&shell.env);
	return (0);
}
