/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:22:50 by dslaveev          #+#    #+#             */
/*   Updated: 2024/03/09 16:16:42 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief finds the first occurence of character in a string
/// @param str
/// @param character
/// @return the pointer to the location if found
char	*ft_strchr(const char *str, int character)
{
	char	c;

	c = (char) character;
	while (*str)
	{
		if (*str == c)
			return ((char *)str);
		str++;
	}
	if (*str == c)
	{
		return ((char *)str);
	}
	return (NULL);
}
