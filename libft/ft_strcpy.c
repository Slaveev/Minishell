/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 20:31:39 by dslaveev          #+#    #+#             */
/*   Updated: 2024/03/09 16:17:15 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief copies a string source to string destination
/// @param dest
/// @param src
/// @return new destination string
char	*ft_strcpy(char *dest, char *src)
{
	char	*ret;

	ret = dest;
	while (*src)
		*(dest++) = *(src++);
	return (ret);
}
