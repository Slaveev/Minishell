/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dslaveev <dslaveev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:18:04 by dslaveev          #+#    #+#             */
/*   Updated: 2024/03/29 13:29:38 by dslaveev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief count how many total words are in a string
/// @param s
/// @param c
/// @return counted words
static size_t	count_words(char const *s, char c)
{
	size_t	count;
	size_t	encounter;

	count = 0;
	encounter = 0;
	while (*s)
	{
		if (*s != c && encounter == 0)
		{
			count++;
			encounter = 1;
		}
		else if (*s == c)
			encounter = 0;
		s++;
	}
	return (count);
}

/// @brief gets each length of a word in the string
/// @param str
/// @param c
/// @return length of each word
static size_t	get_word_len(char const *str, char c)
{
	size_t	i;

	i = 0;
	while (*(str + i) && *(str + i) != c)
		i++;
	return (i);
}

/// @brief frees the inside of the array and the whole array
/// @param i
/// @param array
static void	free_array(size_t i, char **array)
{
	while (i > 0)
	{
		i--;
		free(*(array + i));
	}
	free(array);
}

/// @brief creates the new array with substr and then it frees it
/// @param s
/// @param c
/// @param array
/// @param words_count
/// @return new array
static char	**split(char const *s, char c, char **array, size_t words_count)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < words_count)
	{
		while (*(s + j) && *(s + j) == c)
			j++;
		*(array + i) = ft_substr(s, j, get_word_len(&*(s + j), c));
		if (!*(array + i))
		{
			free_array(i, array);
			return (NULL);
		}
		while (*(s + j) && *(s + j) != c)
			j++;
		i++;
	}
	*(array + i) = NULL;
	return (array);
}

/// @brief splits string into an array of substrings based on delimeter
/// @param s
/// @param c
/// @return sub array
char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	array = (char **)malloc(sizeof(char *) * (words + 1));
	if (!array)
		return (NULL);
	array = split(s, c, array, words);
	return (array);
}
