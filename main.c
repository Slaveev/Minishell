/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:59:54 by dslaveev          #+#    #+#             */
/*   Updated: 2024/06/14 13:23:27 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	execute_command(char *command, char **args)
{
	pid_t	pid;
	int		status;

	if (is_builtin(command))
	{
		printf("not ok\n");
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		if (execvp(command, args) == -1)
			perror("balkanshell");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		perror("balkanshell");
	else
	{
		do
		{
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}

int main(int argc, char **argv, char **env)
{
	char		*prompt;
	char		*input;
	t_lexer		lexer;
	t_parser	*parser;

	env = NULL;
	argv = NULL;
	if (argc > 1)
		return (printf("Error: too many arguments\n"), 1);
	prompt = set_prompt("balkanshell$ ");
	while (1)
	{
		input = readline(prompt);
		init_lexer(&lexer, input);
		parser = init_parser(&lexer);
		parse(parser);
	}
	free(prompt);
}
// need two global var
// nextToken
// resultTree
// how it should work

// 1 scanToken()
// 2 resultTree = parseE()
// 3 if nextToken != EOF
// 4 error()
// 5 printTree(resultTree)

// make while loop to first check if its a builtin
	// if it is execute builtin
// else its not a builtin so we need to fork and run the command
	// exec the command

// parseexec - redir { aaa redir }+
// parseredirs - { > < >> aaa}
// pipe - exec [| pipe]
// parseline - pipe {&} [; line]
// block - (line) redir

// pipe -> exec
// pipe -> exec | pipe

// aaa || (bbb | (ccc | ddd))
			// pipe
		  //    |
		// exec	  pipe
		//  aaa    |
	//       exec     pipe
	//       bbb       |
	//  		  exec     pipe
			//	  ccc       |
						// exec
						// ddd

// first one should be a command
// after the first one should be an argument
// if its a pipe then we are expecting a command
