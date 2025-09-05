/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnogueir <jnogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:12:36 by jnogueir          #+#    #+#             */
/*   Updated: 2025/08/05 17:14:31 by jnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	count_words(const char *s, char c)
{
	int	count;
	int	word;

	count = 0;
	word = 0;
	while (*s)
	{
		if (*s != c && word == 0)
		{
			word = 1;
			count++;
		}
		else if (*s == c)
			word = 0;
		s++;
	}
	return (count);
}

static	char	*extract_next_word(const char *s, char c, int *index)
{
	size_t	end;
	size_t	start;

	if (!s)
		return (NULL);
	end = *index;
	while (s[end] == c)
		end++;
	start = end;
	while (s[end] && s[end] != c)
		end++;
	*index = end;
	if (end > start)
		return (ft_substr(s, start, end - start));
	return (NULL);
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	int		i;
	int		end;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	result = malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	end = 0;
	i = 0;
	while (i < words)
		result[i++] = extract_next_word(s, c, &end);
	result[i] = NULL;
	return (result);
}
