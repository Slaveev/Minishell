/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: jsamardz <jsamardz@student.42heilnronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:59:54 by dslaveev          #+#    #+#             */
/*   Updated: 2024/06/26 14:06:24 by jsamardz         ###   ########.fr       */
=======
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:59:54 by dslaveev          #+#    #+#             */
/*   Updated: 2024/08/01 20:57:03 by jsamardz         ###   ########.fr       */
>>>>>>> workbulgaria
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/parser.h"

t_sig	g_sig = {.status = 0};

char	*set_prompt(char *input)
{
	char	*prompt;

	if (input == NULL)
		return (NULL);
	prompt = malloc(ft_strlen(input) + 1);
	if (prompt == NULL)
	{
		printf("Error: malloc failed\n");
		exit(1);
	}
	ft_strcpy(prompt, input);
	return (prompt);
}

int	process_input(char *input)
{
	if (input == NULL || *input == '\0' || is_only_whitespace(input))
		return (0);
	return (1);
}

static void	init_shell(t_shell_env *shell, char **env)
{
	init_env(&shell->env, env);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

static void	shell_loop(t_shell_env shell)
{
	char		*prompt;
	char		*input;
	t_parser	*parser;

<<<<<<< HEAD
	argv = NULL;
	argc = 0;
	signal_setup();
	if (argc > 1)
		return (printf("Error: too many arguments\n"), 1);
	prompt = set_prompt("balkanshell$ ");
=======
>>>>>>> workbulgaria
	while (1)
	{
		prompt = set_prompt("balkanshell$ ");
		input = readline(prompt);
<<<<<<< HEAD
		if (input == NULL)
			break ;
		init_lexer(&lexer, input);
		parser = init_parser(&lexer);
		parse_command(parser, &cmd, env);
		free_cmd_list(cmd);
		cmd = NULL;
=======
		free(prompt);
		help_eof(input);
		if (!process_input(input))
		{
			free(input);
			continue ;
		}
		add_history(input);
		init_lexer(&shell.lexer, input);
		parser = init_parser(&shell.lexer);
		parse_command(parser, &shell.cmd, &shell.env);
		destroy_lexer(&shell.lexer);
		free_cmd_list(shell.cmd);
		shell.cmd = NULL;
		free(parser);
>>>>>>> workbulgaria
		free(input);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell_env	shell;

	(void)argv;
	(void)argc;
	init_shell(&shell, env);
	shell_loop(shell);
	return (0);
}
