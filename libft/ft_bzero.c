/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:40:10 by dslaveev          #+#    #+#             */
/*   Updated: 2024/03/29 13:29:11 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* @brief Fills string with zeros
*  @params void *dst size_t n
*/
void	ft_bzero(void *dst, size_t n)
{
	ft_memset(dst, 0, n);
}

// char *c;
// size_t i;

// c = dst;
// i = 0;
// while (i < n)
// {
// 	c[i] = '\0';
// 	i++;
// }
