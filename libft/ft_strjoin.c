/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 21:41:12 by dslaveev          #+#    #+#             */
/*   Updated: 2024/03/29 13:29:51 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief joins string to at the end of string 1
/// @param s1
/// @param s2
/// @return a pointer of the joined strings
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size;
	char	*ret;
	char	*dub;

	if (!s1 || !s2)
	{
		if (s1)
			return (ft_strdup(s1));
		else if (s2)
			return (ft_strdup(s2));
		else
			return (ft_strdup(""));
	}
	size = (size_t)(ft_strlen(s1) + (size_t)ft_strlen(s2));
	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (!ret)
		return (NULL);
	dub = ret;
	while (*s1)
		*ret++ = *s1++;
	while (*s2)
		*ret++ = *s2++;
	*ret = '\0';
	return (dub);
}

// int main()
// {
//     char *result;

//     // Test case: Concatenating "Hello, " and "world!"
//     result = ft_strjoin("Hello, ", "world!");
//     printf("Result: \"%s\"\n", result);
//     free(result);

//     return 0;
// }
