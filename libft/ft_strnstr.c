/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:55:51 by dslaveev          #+#    #+#             */
/*   Updated: 2024/03/09 16:33:10 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief searches for a substring in a string with specified length
/// @param haystack
/// @param needle
/// @param len
/// @return substring if found if not NULL
char	*ft_strnstr(char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!needle[i])
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (ft_strncmp(&haystack[i + j], &needle[j], 1) == 0
			&& (i + j) < len)
		{
			if (!haystack[i + j] && !needle[j])
				return ((char *)&haystack[i]);
			j++;
		}
		if (!needle[j])
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
