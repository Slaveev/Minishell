/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:59:54 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/29 15:49:38 by dslaveev         ###   ########.fr       */
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
		// free(input);
		return (0);
	}
	return (1);
}

void	leaks(void)
{
	system("leaks minishell");
}

void free_env_vars(t_env *env)
{
    t_env_var *current = env->vars;
    t_env_var *next;

    while (current != NULL)
    {
        next = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = next;
    }

    env->vars = NULL; // Ensure the pointer is set to NULL after freeing
    if (env->curr_dir != NULL)
    {
        free(env->curr_dir); // Free the current directory string if it's set
        env->curr_dir = NULL;
    }
}

void free_lexer(t_lexer *lexer)
{
    if (lexer != NULL)
    {
        free(lexer->input); // Assuming input is dynamically allocated
        // Free other dynamically allocated members of lexer here
        free(lexer);
    }
}

void free_token(t_tok *token)
{
    if (token != NULL)
    {
        free(token->value); // Assuming value is dynamically allocated
        // Free other dynamically allocated members of token here
        free(token);
    }
}

void	free_parser(t_parser *parser)
{
	if (parser != NULL)
	{
		free_lexer(parser->lexer);
		free_token(parser->current_token);
		free(parser);
	}
}

void ftcleanup(t_shell_env *shell) {
    free_env_vars(&shell->env); // Assuming this frees all env vars
    clear_history(); // Clear the history list to prevent memory leaks
    // Add any other cleanup tasks here
}

void	ftcleanup_wrapper(t_shell_env *shell)
{
	ftcleanup(shell);
	printf("exit\n");
	exit(g_sig.status);
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
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		prompt = set_prompt("balkanshell$ ");
		input = readline(prompt);
		if (!input)
			handle_eof();
		if (!process_input(input))
			continue ;
		add_history(input);
		init_lexer(&shell.lexer, input);
		parser = init_parser(&shell.lexer);
		parse_command(parser, &shell.cmd, &shell.env);
		destroy_lexer(&shell.lexer);
		free_cmd_list(shell.cmd);
		shell.cmd = NULL;
	}
	return (0);
}
