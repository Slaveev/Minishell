/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:40:00 by dslaveev          #+#    #+#             */
/*   Updated: 2024/03/29 13:29:46 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief allocates memory to copy a string
/// @param src
/// @return pointer to the coppied string
char	*ft_strdup(const char *src)
{
	char	*dub_ptr;
	char	*ptr;
	int		src_size;

	src_size = (int)(ft_strlen(src));
	ptr = (char *)malloc(sizeof(char) * (src_size + 1));
	if (!ptr)
		return (NULL);
	dub_ptr = ptr;
	while (*src)
	{
		*ptr = *src;
		ptr++;
		src++;
	}
	*ptr = '\0';
	return (dub_ptr);
}
