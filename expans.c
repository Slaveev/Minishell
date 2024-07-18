

// // Helper function to free a string and set its pointer to NULL
// void null_check_free_str(char *str) {
//     if (str) {
//         free(str);
//         str = NULL;
//     }
// }

// char	*ft_strncat(char *s1, char *s2, int n)
// {
// 	char	*str;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	if (!s1 && !s2)
// 		return (NULL);
// 	str = (char *)malloc((ft_strlen(s1) + n + 1) * sizeof(char));
// 	if (!str)
// 		return (NULL);
// 	while (s1 && *(s1 + i) != '\0')
// 	{
// 		*(str + i) = *(s1 + i);
// 		i++;
// 	}
// 	j = -1;
// 	while (++j < n && s2 && *(s2 + j) != '\0')
// 		*(str + i + j) = *(s2 + j);
// 	*(str + i + j) = '\0';
// 	return (null_check_free_str(s1), str);
// }

// char *expand_env_variables(const char *input, t_env *env) {
//     size_t result_size = 1024;
//     char *result = malloc(result_size);
//     if (!result)
//         ft_error("Memory allocation failed", 1);

//     int result_len = 0;
//     int i = 0;
// 	printf("hi\n");
//     while (input[i] != '\0') {
//         if (input[i] == '$') {
//             i++;
//             char var_name[256];
//             int var_len = 0;

//             while (input[i] != '\0' && (isalnum(input[i]) || input[i] == '_')) {
//                 if (var_len < 255) {
//                     var_name[var_len++] = input[i];
//                 }
//                 i++;
//             }
//             var_name[var_len] = '\0';

//             char *value = get_env_var(env, var_name);
//             if (value) {
//                 size_t value_len = strlen(value);
//                 if (result_len + value_len >= result_size) {
//                     result_size *= 2;
//                     result = realloc(result, result_size);
//                     if (!result)
//                         ft_error("Memory reallocation failed", 1);
//                 }
//                 strcpy(result + result_len, value);
//                 result_len += value_len;
//             }
//         } else {
//             if (result_len + 1 >= (int)result_size) {
//                 result_size *= 2;
//                 result = realloc(result, result_size);
//                 if (!result)
//                     ft_error("Memory reallocation failed", 1);
//             }
//             result[result_len++] = input[i++];
//         }
//     }

//     result[result_len] = '\0';
//     return result;
// }


// // char *expand_env_variables(const char *input, t_env *env) {
// //     char *result = malloc(1024); // Allocate memory for the result
// //     if (!result)
// //         ft_error("Memory allocation failed", 1);

// //     int result_len = 0;
// //     int i = 0;

// //     while (input[i] != '\0') {
// //         if (input[i] == '$') {
// //             i++;
// //             char var_name[256];
// //             int var_len = 0;

// //             while (input[i] != '\0' && (isalnum(input[i]) || input[i] == '_')) {
// //                 var_name[var_len++] = input[i++];
// //             }
// //             var_name[var_len] = '\0';

// //             char *value = get_env_var(env, var_name);
// //             if (value) {
// //                 strcpy(result + result_len, value);
// //                 result_len += strlen(value);
// //             }
// //         } else {
// //             result[result_len++] = input[i++];
// //         }
// //     }

// //     result[result_len] = '\0';
// //     return result;
// // }

// char *expand_tilde(const char *input, t_env *env) {
//     if (input[0] != '~')
//         return strdup(input);

//     char *home_dir = get_env_var(env, "HOME");
//     if (!home_dir)
//         return strdup(input);

//     char *result = malloc(strlen(home_dir) + strlen(input));
//     if (!result)
//         ft_error("Memory allocation failed", 1);

//     strcpy(result, home_dir);
//     strcat(result, input + 1);

//     return result;
// }

// void process_single_quotes(char *arg, int *i, char **to_expand) {
//     (*i)++; // Skip the opening single quote
//     while (*(arg + *i) && strncmp((arg + *i), "'", 1) != 0) {
//         *to_expand = strncat(*to_expand, (arg + *i), 1);
//         (*i)++;
//     }
//     if (*(arg + *i) == '\'') (*i)++; // Skip the closing single quote
// }

// char *extract_var_name(char *arg, int *i) {
//     int start = *i;
//     int len = 0;
//     while (arg[*i] && (isalnum(arg[*i]) || arg[*i] == '_')) {
//         (*i)++;
//         len++;
//     }
//     char *var_name = (char *)malloc(len + 1);
//     if (!var_name) return NULL; // Check for malloc failure
//     strncpy(var_name, arg + start, len);
//     var_name[len] = '\0';
//     return var_name;
// }


// int process_expansion(t_env *env, char *arg, int *i, char **to_expand) {
// 	printf("find\n");
//     (*i)++; // Skip the '$' character
//     char *var_name = extract_var_name(arg, i);
//     if (!var_name) return 0;

//     char *value = get_env_var(env, var_name);
//     free(var_name);

//     if (value) {
//         *to_expand = strncat(*to_expand, value, strlen(value));
//         return 1;
//     }
//     return 0;
// }

// void process_double_quotes(t_env *env, char *arg, int *i, char **to_expand) {
//     (*i)++; // Skip the opening double quote
//     while (arg[*i] && arg[*i] != '\"') {
//         if (arg[*i] == '$' && arg[*i + 1] != '\0') {
//             if (process_expansion(env, arg, i, to_expand)) {
//                 continue;
//             }
//         } else {
//             *to_expand = strncat(*to_expand, &arg[*i], 1);
//             (*i)++;
//         }
//     }
//     if (arg[*i] == '\"') (*i)++; // Skip the closing double quote
// }

// char *expansion_process_succeeded(t_cmd *cmd, t_env *env, char *arg, char **to_expand, int *flag_rf) {
//     int i = 0;
//     size_t to_expand_size = strlen(*to_expand) + 1; // Initial size of to_expand
//     (void)cmd;

//     while (*(arg + i)) {
//         if (strncmp((arg + i), "'", 1) == 0)
//             process_single_quotes(arg, &i, to_expand);
//         else if (strncmp((arg + i), "\"", 1) == 0)
//             process_double_quotes(env, arg, &i, to_expand);
//         else if (strncmp((arg + i), "$", 1) == 0 && *(arg + i + 1) != '\0') {
//             if (process_expansion(env, arg, &i, to_expand))
//                 *flag_rf = 1;
//             i++;
//         } else {
//             // Ensure there's enough space in *to_expand to hold the new character and null terminator
//             if (strlen(*to_expand) + 2 > to_expand_size) {
//                 to_expand_size *= 2; // Double the buffer size
//                 *to_expand = realloc(*to_expand, to_expand_size);
//                 if (*to_expand == NULL) {
//                     fprintf(stderr, "Memory allocation failed\n");
//                     exit(1);
//                 }
//             }

//             char temp[2] = {*(arg + i), '\0'}; // Temporary buffer to hold the character and null terminator
//             strncat(*to_expand, temp, 1); // Correct usage of strncat
//             i++;
//         }
//     }
//     return *to_expand;
// }


// int is_needed_expansion(t_cmd *cmd, t_env *env, char **args, int *flag_rf) {
//     char *to_expand = NULL;
//     char *arg = *args;
//     if (expansion_process_succeeded(cmd, env, arg, &to_expand, flag_rf)) {
// 		printf("hi\n");
//         null_check_free_str(arg);
//         *args = to_expand;
//         return 1;
//     }
//     return 0;
// }

// void	unshift_element(char **args, int *pos)
// {
// 	int	j;
// 	int	i;

// 	j = -1;
// 	i = *pos - 1;
// 	while (*(args + ++j))
// 		;
// 	if (*(args + *pos))
// 		null_check_free_str(*(args + *pos));
// 	while (++i < j - 1)
// 		*(args + i) = *(args + i + 1);
// 	*(args + j - 1) = NULL;
// 	(*pos)--;
// }


// char **concat_arrays(char **args, char **inserted_args, int i, int *flag_rf) {
//     int len_args = 0, len_inserted = 0;
//     while (args[len_args] != NULL) len_args++;
//     while (inserted_args[len_inserted] != NULL) len_inserted++;

//     // New size will be the sum of both arrays minus 1 (since one element is replaced)
//     char **new_args = malloc(sizeof(char *) * (len_args + len_inserted));
//     if (!new_args) return NULL; // Memory allocation check

//     // Copy elements from `args` up to index `i`
//     for (int j = 0; j < i; j++) {
//         new_args[j] = strdup(args[j]);
//     }

//     // Insert `inserted_args`
//     for (int j = 0; j < len_inserted; j++) {
//         new_args[i + j] = strdup(inserted_args[j]);
//     }

//     // Copy remaining elements from `args` after index `i`
//     for (int j = i + 1; j < len_args; j++) {
//         new_args[j + len_inserted - 1] = strdup(args[j]);
//     }

//     // Null-terminate the new array
//     new_args[len_args + len_inserted - 1] = NULL;

//     // Free the original `args` array and its strings
//     for (int j = 0; args[j] != NULL; j++) {
//         free(args[j]);
//     }
//     free(args);

//     // Update the flag to indicate the operation is complete
//     *flag_rf = 0;

//     return new_args;
// }

// void passed_expansion_process(t_cmd_node *cmd_list, t_env *env) {
//     t_cmd_node *temp_cmds = cmd_list;
//     int i;
//     int flag_rf;

//     flag_rf = 0;
//     while (temp_cmds) {
//         i = -1;
//         while (temp_cmds->cmd->args && *(temp_cmds->cmd->args + ++i)) {
//             if (!is_needed_expansion(temp_cmds->cmd, env, (temp_cmds->cmd->args + i), &flag_rf))
// 			{
// 				printf("here\n");
//                 unshift_element(temp_cmds->cmd->args, &i);
// 			}
//             if (flag_rf)
//                 temp_cmds->cmd->args = concat_arrays(temp_cmds->cmd->args, ft_split(*(temp_cmds->cmd->args + i), ' '), i, &flag_rf);
//         }
//         temp_cmds = temp_cmds->next;
//     }
// }
