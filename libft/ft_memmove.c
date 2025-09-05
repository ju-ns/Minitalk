/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnogueir <jnogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 20:44:13 by marvin            #+#    #+#             */
/*   Updated: 2025/08/05 16:58:36 by jnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*copy;
	const unsigned char	*src_char;
	size_t				i;

	copy = (unsigned char *) dest;
	src_char = (const unsigned char *) src;
	if (!dest && !src)
		return (NULL);
	if (copy > src_char)
	{
		i = n;
		while (i > 0)
		{
			i--;
			copy[i] = src_char[i];
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
