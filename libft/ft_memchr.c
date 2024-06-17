/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 18:41:53 by dslaveev          #+#    #+#             */
/*   Updated: 2024/03/09 15:57:07 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief finds the first occurance in a string of memory bytes
/// @param s
/// @param c
/// @param n
/// @return returns a pointer to the byte located
void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;
	unsigned char		uc;
	size_t				i;

	str = (unsigned char *) s;
	uc = c;
	i = 0;
	if (n == 0)
		return (NULL);
	while (n > i)
	{
		if (*(str + i) == uc)
			return ((void *)(str + i));
		i++;
	}
	return (NULL);
}
