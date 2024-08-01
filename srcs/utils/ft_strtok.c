/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsamardz <jsamardz@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 20:21:40 by jsamardz          #+#    #+#             */
/*   Updated: 2024/08/01 20:49:18 by jsamardz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef struct s_bufferinfo
{
	size_t	size;
	size_t	index;
}	t_bufferinfo;

static void	handle_format_specifier(const char **p, va_list args, char *buffer,
	t_bufferinfo *bufinfo)
{
	const char	*str;

	if (**p == 's')
	{
		str = va_arg(args, const char *);
		while (*str && bufinfo->index < bufinfo->size - 1)
			buffer[bufinfo->index++] = *str++;
	}
	else
	{
		if (bufinfo->index < bufinfo->size - 1)
			buffer[bufinfo->index++] = '%';
		if (**p && bufinfo->index < bufinfo->size - 1)
			buffer[bufinfo->index++] = **p;
	}
}

int	ft_snprintf(char *buffer, size_t size, const char *format, ...)
{
	va_list			args;
	t_bufferinfo	bufinfo;
	const char		*p;

	va_start(args, format);
	p = format;
	bufinfo.index = 0;
	bufinfo.size = size;
	while (*p && bufinfo.index < size - 1)
	{
		if (*p == '%')
		{
			p++;
			handle_format_specifier(&p, args, buffer, &bufinfo);
		}
		else
			buffer[bufinfo.index++] = *p;
		p++;
	}
	buffer[bufinfo.index] = '\0';
	va_end(args);
	return ((int)bufinfo.index);
}

char	*ft_strpbrk(const char *str1, const char *str2)
{
	const char	*s1;
	const char	*s2;

	s1 = str1;
	while (*s1 != '\0')
	{
		s2 = str2;
		while (*s2 != '\0')
		{
			if (*s1 == *s2)
				return ((char *)s1);
			s2++;
		}
		s1++;
	}
	return (NULL);
}

size_t	ft_strspn(const char *str1, const char *str2)
{
	const char	*s1;
	const char	*s2;
	size_t		count;

	s1 = str1;
	count = 0;
	while (*s1 != '\0')
	{
		s2 = str2;
		while (*s2 != '\0')
		{
			if (*s1 == *s2)
				break ;
			s2++;
		}
		if (*s2 == '\0')
			return (count);
		count++;
		s1++;
	}
	return (count);
}

char	*ft_strtok(char *str, const char *delim)
{
	static char	*saved_str;
	char		*token;

	if (str != NULL)
		saved_str = str;
	if (saved_str == NULL)
		return (NULL);
	saved_str += ft_strspn(saved_str, delim);
	if (*saved_str == '\0')
	{
		saved_str = NULL;
		return (NULL);
	}
	token = saved_str;
	saved_str = ft_strpbrk(token, delim);
	if (saved_str != NULL)
	{
		*saved_str = '\0';
		saved_str++;
	}
	return (token);
}
