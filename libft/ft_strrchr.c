/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 09:37:07 by dslaveev          #+#    #+#             */
/*   Updated: 2024/03/09 16:33:41 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief finds the last occurence of c in a string
/// @param str
/// @param character
/// @return a pointer to its location
char	*ft_strrchr(const char *str, int character)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	while (i >= 0)
	{
		if (str[i--] == (char)character)
			return ((char *)str + i + 1);
	}
	return (0);
}
