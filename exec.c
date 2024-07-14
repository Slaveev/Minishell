/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:41:17 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/14 11:10:18 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

char *find_command_in_path(char *command, t_env *env)
{
    t_env_var *current = env->vars;
    char *path_env = NULL;

    while (current != NULL)
    {
        if (strncmp(current->key, "PATH", 4) == 0 && current->key[4] == '\0')
        {
            path_env = current->value;
            break;
        }
        current = current->next;
    }

    if (path_env == NULL)
    {
        return NULL;
    }

    char *path = strdup(path_env);
    char *token = strtok(path, ":");
    char full_path[1024];
    while (token != NULL)
    {
        snprintf(full_path, sizeof(full_path), "%s/%s", token, command);
        if (access(full_path, X_OK) == 0)
        {
            free(path);
            return strdup(full_path);
        }
        token = strtok(NULL, ":");
    }

    free(path);
    return NULL;
}

// char **env_to_char_array(t_env *env)
// {
//     int count = 0;
//     t_env_var *current = env->vars;

//     while (current != NULL)
//     {
//         count++;
//         current = current->next;
//     }

//     char **envp = malloc(sizeof(char *) * (count + 1));
//     if (envp == NULL)
//     {
//         perror("malloc failed");
//         exit(1);
//     }

//     current = env->vars;
//     for (int i = 0; i < count; i++)
//     {
//         size_t len = strlen(current->key) + strlen(current->value) + 2;
//         envp[i] = malloc(len);
//         if (envp[i] == NULL)
//         {
//             perror("malloc failed");
//             exit(1);
//         }
//         snprintf(envp[i], len, "%s=%s", current->key, current->value);
//         current = current->next;
//     }
//     envp[count] = NULL;

//     return envp;
// }

// void free_char_array(char **array)
// {
//     if (array)
//     {
//         for (int i = 0; array[i] != NULL; i++)
//         {
//             free(array[i]);
//         }
//         free(array);
//     }
// }

void ft_execute(t_cmd_node *cmd_list, t_env *env)
{
    t_cmd_node *current_node = cmd_list;

    while (current_node != NULL)
    {
        if (is_builtin(current_node->cmd->command))
        {
            builtin_exec(current_node->cmd->args, env);
            return;
        }
        t_cmd *cmd = current_node->cmd;
        char *cmd_path;
        int fd_input = -1, fd_output = -1;
        int pipe_fd[2] = {-1, -1};

        if (cmd->command)
            printf("cmd->command: %s\n", cmd->command);
        // Input redirection
        if (cmd->fd_in)
        {
            fd_input = open(cmd->fd_in, O_RDONLY);
            if (fd_input == -1)
                ft_error("Failed to open input file", 1);
        }
        // Output redirection
        if (cmd->fd_out)
        {
            printf("cmd->fd_out: %s\n", cmd->fd_out);
            fd_output = open(cmd->fd_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_output == -1)
                ft_error("Failed to open output file", 1);
        }
        // Pipe handling
        if (cmd->pipe && pipe(pipe_fd) == -1)
            ft_error("Failed to create pipe", 1);

        cmd->pid = fork();
        if (cmd->pid == 0)
        { // Child process
            // Input redirection
            if (fd_input != -1)
            {
                if (dup2(fd_input, STDIN_FILENO) == -1)
                    ft_error("Failed to redirect stdin", 1);
                close(fd_input);
            }
            // Output redirection
            if (fd_output != -1)
            {
                if (dup2(fd_output, STDOUT_FILENO) == -1)
                    ft_error("Failed to redirect stdout", 1);
                close(fd_output);
            }
            // Pipe handling
            if (cmd->pipe)
            {
                close(pipe_fd[0]);
                if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
                    ft_error("Failed to redirect stdout", 1);
                close(pipe_fd[1]);
            }
            if (cmd->command[0] == '/')
                cmd_path = cmd->command;
            else
                cmd_path = find_command_in_path(cmd->command, env);
            if (cmd_path) // Check
                printf("cmd_path: %s\n", cmd_path);
            else
                ft_error("Command not found", 127);

            // Convert t_env to char ** array for execve
            char **envp = env_to_char_array(env);

            // Execute the command with the current environment
            if (execve(cmd_path, current_node->cmd->args, envp) == -1)
                ft_error("Command not executable", 126);

            // Free the allocated environment array
            free_char_array(envp);
        }
        // Parent process
        if (fd_input != -1) close(fd_input);
        if (fd_output != -1) close(fd_output);
        if (cmd->pipe)
        {
            close(pipe_fd[1]);
        }
        waitpid(cmd->pid, &cmd->status, 0);
        current_node = current_node->next;
    }
}
