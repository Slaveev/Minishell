/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:45:18 by dslaveev          #+#    #+#             */
/*   Updated: 2024/03/09 16:35:41 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief checks whether the index of string matches character c
/// @param str
/// @param c
static size_t	check_set(char const *str, char const c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/// @brief allocates memory for a new string
/// @param s1
/// @param start
/// @param len
/// @return a pointer to the new string
static char	*create_new(const char *s1, size_t start, size_t len)
{
	char	*str;
	size_t	i;

	if (len <= 0 || start >= ft_strlen(s1))
		return (ft_strdup(""));
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s1[start + i];
		i++;
	}
	return (str);
}

/// @brief trims the string from set characters
/// @param s1
/// @param set
/// @return returns the trimmed string
char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;

	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && check_set(set, s1[start]))
		start++;
	while (end > start && check_set(set, s1[end]))
		end--;
	return (create_new(s1, start, end - (start - 1)));
}
