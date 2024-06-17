/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:53:49 by dslaveev          #+#    #+#             */
/*   Updated: 2024/03/29 13:30:14 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief searches for a substring in a string
/// @param s
/// @param start
/// @param len
/// @return substring that was searched
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	if (len >= ft_strlen(s + start))
		len = ft_strlen(s + start);
	ptr = ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*ptr;
// 	size_t	i;

// 	if (!s)
// 		return (NULL);
// 	if (start > len)
// 		return (ft_strdup(""));
// 	i = 0;
// 	if (len >= ft_strlen(s + start))
// 		len = ft_strlen(s + start);
// 	ptr = ft_calloc(len + 1, sizeof(char));
// 	if (!ptr)
// 		return (NULL);
// 	while (i < len)
// 	{
// 		ptr[i] = s[start + i];
// 		i++;
// 	}
// 	ptr[i] = '\0';
// 	return (ptr);
// }
