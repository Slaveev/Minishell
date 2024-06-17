/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:16:34 by dslaveev          #+#    #+#             */
/*   Updated: 2024/03/09 16:29:43 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief appends src string to the end of dest string
/// @param dest
/// @param src
/// @param size
/// @return total length of the new dest string
size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t		dest_len;
	size_t		total_len;
	const char	*s;

	if ((!dest || !src) && !size)
		return (0);
	dest_len = 0;
	s = src;
	while (*(dest + dest_len) && dest_len < size)
		dest_len++;
	if (dest_len < size)
		total_len = dest_len + (int )(ft_strlen(s));
	else
		return (size + ft_strlen(s));
	while (*s && dest_len + 1 < size)
	{
		dest[dest_len] = *s++;
		dest_len++;
	}
	dest[dest_len] = '\0';
	return (total_len);
}
