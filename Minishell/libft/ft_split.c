/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trarijam <trarijam@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:49:07 by trarijam          #+#    #+#             */
/*   Updated: 2024/08/22 15:24:07 by trarijam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	words;
	int		in_words;

	in_words = 0;
	words = 0;
	while (*s)
	{
		if (*s != c && !in_words)
		{
			in_words = 1;
			words++;
		}
		else if (*s == c)
			in_words = 0;
		s++;
	}
	return (words);
}

static size_t	len_word(char const *s, char c, int start)
{
	size_t	i;

	i = 0;
	while (s[start + i] != c && s[start + i] != '\0')
		i++;
	return (i);
}

static void	split(char const *s, char c, size_t words, char **tab)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (j < words)
	{
		while (s[i] == c)
			i++;
		tab[j] = (char *)malloc(sizeof(char) * (len_word(s, c, i) + 1));
		while (k < len_word(s, c, i) + 1 && s[i + k] != '\0' && s[i + k] != c)
		{
			tab[j][k] = s[i + k];
			k++;
		}
		tab[j][k] = '\0';
		k = 0;
		i += len_word(s, c, i);
		j++;
	}
	tab[j] = NULL;
}

char	**ft_split(char const *s, char c)
{
	size_t	words;
	char	**tab;

	if (s == NULL)
		return (NULL);
	words = count_words(s, c);
	tab = (char **)malloc(sizeof(char *) * (words + 1));
	if (tab == NULL)
		return (NULL);
	split(s, c, words, tab);
	return (tab);
}
