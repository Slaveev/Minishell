/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:04:18 by dslaveev          #+#    #+#             */
/*   Updated: 2024/03/09 16:06:01 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief compare bytes from str1
/// @param str1
/// @param str2
/// @param n
/// @return 0 if their indentical otherwise the difference between them
int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	const unsigned char	*s1;
	const unsigned char	*s2;

	s1 = str1;
	s2 = str2;
	if (n == 0)
		return (0);
	while ((*s1 == *s2) && n - 1 > 0)
	{
		s1++;
		s2++;
		n--;
	}
	return ((int)(*s1 - *s2));
}
