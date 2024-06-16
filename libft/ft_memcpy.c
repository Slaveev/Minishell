/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:04:51 by dslaveev          #+#    #+#             */
/*   Updated: 2024/03/09 16:06:50 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief copy memory from one place to another
/// @param dst
/// @param src
/// @param n
/// @return the destination that is coppied
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dst && !src)
		return (NULL);
	d = dst;
	s = src;
	while (n > 0)
	{
		*d++ = *s++;
		n--;
	}
	return (dst);
}
