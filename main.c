/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 10:59:54 by dslaveev          #+#    #+#             */
/*   Updated: 2024/06/13 12:54:29 by dslaveev         ###   ########.fr       */
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
void	handle_pwd(void)
{
	char	pwd[1024];

	if (getcwd(pwd, sizeof(pwd)) != NULL)
		printf("%s\n", pwd);
	else
		perror("getcwd() error");
}

void	handle_cd(char *input)
{
	char	*dir;
	char	new_path[1024];

	dir = input + 2;
	while (*dir == ' ' || *dir == '\t')
		dir++;
	if (strlen(dir) == 0)
		dir = getenv("HOME");
	if (chdir(dir) != 0)
		perror("chdir() error");
	else
		if (getcwd(new_path, sizeof(new_path)) == NULL)
			perror("getcwd() error");
}

void handle_type(char *input)
{
	char	*command;

	command = input + 5;
	if ((strncmp(command, "exit", 4) == 0 && strlen(command) == 4) ||
		(strncmp(command, "echo", 4) == 0 && strlen(command) == 4) ||
		(strncmp(command, "pwd", 3) == 0 && strlen(command) == 3) ||
		(strncmp(command, "cd", 2) == 0 && strlen(command) == 2) ||
		(strncmp(command, "type", 4) == 0 && strlen(command) == 4))
	{
		printf("%s is a shell builtin\n", command);
	}
	else
	{
		printf("%s not found\n", command);
	}
}

void	handle_echo(char *input)
{
	char	*str;
	int		new_line;

	new_line = 1;
	str = input + 4;
	while (*str == ' ' || *str == '\t')
		str++;
	if (!strncmp(str, "-n", 2))
	{
		new_line = 0;
		str += 2;
		while (*str == ' ' || *str == '\t')
			str++;
	}
	// printf("%s\n", input);
	// printf("str = '%s\n'", str);
	printf("%s", str);
	if (new_line)
		printf("\n");
	else
		printf("\r");
}

void	handle_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}

void	builtin_exec(char *input, char **env)
{
	if (!strncmp(input, "env", 4))
		handle_env(env);
	else if (!strncmp(input, "exit", 4) && (strlen(input) == 4))
	{
		printf("exit\n");
		exit(0);
	}
	else if (!strncmp(input, "echo", 4))
		handle_echo(input);
	else if (!strncmp(input, "pwd", 3) && strlen(input) == 3)
		handle_pwd();
	else if (!strncmp(input, "cd", 2) && (input[2] == ' ' || input[2] == '\0'))
		handle_cd(input);
	else if (!strncmp(input, "type ", 5))
		handle_type(input);
	else
		printf("Command not found: %s\n", input);
}

// void	handle_input(char *input, char **env)
// {
// 	if (strlen(input) == 0)
// 		return ;
// 	builtin_exec(input, env);
// 	// run_cmd(input, env);
// }

void	execute_command(char *command, char **args)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(command, args) == -1)
			perror("balkanshell");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("balkanshell");
	}
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
