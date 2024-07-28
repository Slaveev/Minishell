/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:02:25 by dslaveev          #+#    #+#             */
/*   Updated: 2024/07/28 13:46:30 by jsamardz         ###   ########.fr       */
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
	g_sig.status = 0;
}

void	handle_echo(char **input)
{
	int	i;
	int	new_line;

	new_line = 1;
	i = 1;
	if (input[1] && !strcmp(input[1], "$?"))
		printf("%d\n", g_sig.status);
	else
	{
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
	g_sig.status = 0;
}

int	is_num(const char *s)
{
	if (s == NULL || *s == '\0')
		return (0);
	while (*s)
	{
		if (!ft_isdigit(*s) && *s != '-' && *s != '+')
			return (0);
		s++;
	}
	return (1);
}

void	exit_status(char **input)
{
	if (input[1] != NULL)
	{
		if (is_num(input[1]))
			g_sig.status = ft_atoi(input[1]);
		else
		{
			ft_putendl_fd("exit: numeric arg required", 2);
			g_sig.status = 255;
			exit(g_sig.status);
		}
	}
	printf("exit\n");
	exit(g_sig.status);
}
