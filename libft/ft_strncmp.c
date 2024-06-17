/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:27:04 by dslaveev          #+#    #+#             */
/*   Updated: 2024/03/29 13:30:07 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief compare if n indexes of one string to another
/// @param dest
/// @param src
/// @param n
/// @return difference bettwen indexes
int	ft_strncmp(char *dest, const char *src, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)dest;
	str2 = (unsigned char *)src;
	while ((*str1 || *str2) && n > 0)
	{
		if (*(str1++) != *(str2++))
			return (*(str1 - 1) - *(str2 - 1));
		n--;
	}
	return (0);
}
