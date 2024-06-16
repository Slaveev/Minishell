/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:42:28 by dslaveev          #+#    #+#             */
/*   Updated: 2024/03/29 13:29:31 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief sets string with character c len n
/// @param b
/// @param c
/// @param len
/// @return filled pointer
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*dst;

	dst = b;
	while (len > 0)
	{
		*dst = (unsigned char) c;
		dst++;
		len--;
	}
	return (b);
}
