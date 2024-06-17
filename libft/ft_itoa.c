/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:02:49 by dslaveev          #+#    #+#             */
/*   Updated: 2024/03/09 15:53:35 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief helper function for counting digits
/// @param n
/// @return total number of digits
static int	count_digits(int n)
{
	int		count;
	long	nbr;

	count = 0;
	nbr = n;
	if (nbr < 1)
		count++;
	while (nbr)
	{
		nbr = nbr / 10;
		count++;
	}
	return (count);
}

/// @brief converts the number if to its absolute value
/// @param n
/// @return positive number only
static	long	absolute(long long n)
{
	long	nb;

	nb = 1;
	if (n < 0)
		nb *= -n;
	else
		nb *= n;
	return (nb);
}

/// @brief convert integer to character
/// @param n
/// @return an array of characters
char	*ft_itoa(int n)
{
	int		sign;
	int		digits;
	char	*result;
	long	nbr;

	sign = 0;
	if (n < 0)
		sign = 1;
	nbr = absolute(n);
	digits = count_digits(n);
	result = (char *)malloc(sizeof(char) * (digits + 1));
	if (!result)
		return (NULL);
	*(result + digits) = '\0';
	while (digits--)
	{
		result[digits] = 48 + (nbr % 10);
		nbr /= 10;
	}
	if (sign)
		result[0] = '-';
	return (result);
}
