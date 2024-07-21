/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:02:25 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/21 14:34:53 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtin.h"
#include "../../includes/minishell.h"

void	handle_pwd(void)
{
	char	pwd[1024];

	if (getcwd(pwd, sizeof(pwd)) != NULL)
		printf("%s\n", pwd);
	else
		perror("getcwd() error");
}

void	handle_echo(char **input)
{
	int	i;
	int	new_line;

	new_line = 1;
	i = 1;
	while (input[i] && !strcmp(input[i], "-n"))
	{
		new_line = 0;
		i++;
	}
	while (input[i])
	{
		printf("%s", input[i]);
		if (input[i + 1] && input[i][0] != '\0')
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
}
