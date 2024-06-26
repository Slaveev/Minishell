// #include "minishell.h"
// # include <stdio.h>
// # include <stdlib.h>
// # include <string.h>
// # include <fcntl.h>
// # include <sys/wait.h>
// # include <readline/readline.h>
// # include <readline/history.h>
// # include <unistd.h>
// # include "libft/libft.h"

// #define MAX_CMD_LEN 100
// #define MAX_ARGS 10
// // void    ft_execute(t_cmd *cmd, char **env)
// // {
// //     char *cmd_path;
// //     int fd_input, fd_output;
// //     int  pipe_fd[2];

// //     if (cmd->fd_in)
// //     {
// //         fd_input = open(cmd->fd_in, O_RDONLY);
// //         if (fd_input == -1)
// //             ft_error("Failed to open input file", 1);
// //         if (dup2(fd_input, STDIN_FILENO) == -1)
// //             ft_error("Failed to redirect stdin", 1);
// //         close(fd_input);
// //     }
// //     if (cmd->fd_out)
// //     {
// //         printf("cmd->fd_out: %s\n", cmd->fd_out);
// //         fd_output = open(cmd->fd_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// //         if (fd_output == -1)
// //             ft_error("Failed to open output file", 1);
// //         if (dup2(fd_output, STDOUT_FILENO) == -1)
// //             ft_error("Failed to redirect stdout", 1);
// //         close(fd_output);
// //     }
// //     if (is_builtin(cmd->command))
// //     {
// //         builtin_exec(cmd->args, env);
// //         return;
// //     }
// // 	if (cmd->pipe)
// // 	{
// // 		if (pipe(pipe_fd) == -1)
// // 			ft_error("Failed to create pipe", 1);
// // 	}
// //     cmd_path = get_cmd_path(cmd->command, env);
// //     if (!cmd_path)
// //         ft_error("Command not found", 127);
// //     cmd->pid = fork();
// //     if (cmd->pid == -1)
// //         ft_error("Failed to fork", 1);
// //     else if (cmd->pid == 0)
// //     {
// // 		if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
// // 			ft_error("Failed to redirect stdout", 1);
// // 		close(pipe_fd[0]);
// // 		close(pipe_fd[1]);
// //         if (execve(cmd_path, cmd->args, env) == -1)
// //             ft_error("Command not executable", 126);
// //     }
// //     else
// // 	{
// // 		if (cmd->pipe)
// // 			close(pipe_fd[1]);
// //         waitpid(cmd->pid, &cmd->status, 0);
// // 	}
// // }
// // Function to find the full path of a command
// char    *find_command_in_path(char *command, char **envp)
// {
//     char *path_env = NULL;
//     for (int i = 0; envp[i] != NULL; i++) {
//         if (strncmp(envp[i], "PATH=", 5) == 0) {
//             path_env = envp[i] + 5;
//             break;
//         }
//     }
//     if (path_env == NULL) {
//         return NULL;
//     }
//     char *path = strdup(path_env);
//     char *token = strtok(path, ":");
//     char full_path[1024];
//     while (token != NULL)
//     {
//         snprintf(full_path, sizeof(full_path), "%s/%s", token, command);
//         if (access(full_path, X_OK) == 0) {
//             free(path);
//             return strdup(full_path);
//         }
//         token = strtok(NULL, ":");
//     }
//     free(path);
//     return NULL;
// }
// void    execute_command(char *cmd, char **envp)
// {
//     char *args[MAX_ARGS];
//     int i = 0;
//     // Split command into arguments
//     args[i++] = strtok(cmd, " ");
//     while ((args[i++] = strtok(NULL, " ")) != NULL) {
//         if (i >= MAX_ARGS - 1) break;
//     }
//     args[i] = NULL;
//     if (args[0] != NULL) {
//         char *path = find_command_in_path(args[0], envp);
//         if (path != NULL) {
//             // Use execve to execute the command
//             if (execve(path, args, envp) == -1) {
//                 perror("execve");
//                 exit(EXIT_FAILURE);
//             }
//         } else {
//             fprintf(stderr, "Command not found: %s\n", args[0]);
//             exit(EXIT_FAILURE);
//         }
//     }
// }
// int main(int argc, char *argv[], char *envp[])
// {
//     char *command;
//     while (1) {
//         command = readline("Shell> ");
//         if (!command) {
//             break;
//         }
//         // if (strlen(command) > 0) {
//         //     add_history(command);
//         // }
//         char *commands[MAX_CMD_LEN];
//         int num_pipes = 0;
//         // Split by pipes
//         char *token;
//         token = strtok(command, "|");
//         while (token != NULL) {
//             commands[num_pipes++] = token;
//             token = strtok(NULL, "|");
//         }
//         commands[num_pipes] = NULL;
//         int pipefds[2 * (num_pipes - 1)];
//         pid_t pid;
//         int status;
//         int i;
//         // Set up pipes
//         for (i = 0; i < num_pipes - 1; i++) {
//             if (pipe(pipefds + i * 2) == -1) {
//                 perror("pipe");
//                 exit(EXIT_FAILURE);
//             }
//         }
//         for (i = 0; i < num_pipes; i++) {
//             pid = fork();
//             if (pid == -1) {
//                 perror("fork");
//                 exit(EXIT_FAILURE);
//             } else if (pid == 0) {
//                 // Child process
//                 // If not the first command, get input from previous pipe
//                 if (i > 0) {
//                     if (dup2(pipefds[(i - 1) * 2], 0) == -1) {
//                         perror("dup2");
//                         exit(EXIT_FAILURE);
//                     }
//                 }
//                 // If not the last command, send output to next pipe
//                 if (i < num_pipes - 1) {
//                     if (dup2(pipefds[i * 2 + 1], 1) == -1) {
//                         perror("dup2");
//                         exit(EXIT_FAILURE);
//                     }
//                 }
//                 // Close all pipe fds
//                 for (int j = 0; j < 2 * (num_pipes - 1); j++) {
//                     close(pipefds[j]);
//                 }
//                 // Execute command
//                 execute_command(commands[i], envp);
//             }
//         }
//         // Parent process
//         // Close all pipe fds
//         for (i = 0; i < 2 * (num_pipes - 1); i++) {
//             close(pipefds[i]);
//         }
//         // Wait for all child processes
//         for (i = 0; i < num_pipes; i++) {
//             wait(&status);
//         }
//         free(command);
//     }
//     return 0;
// }





