/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnogueir <jnogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 12:32:21 by jnogueir          #+#    #+#             */
/*   Updated: 2025/09/05 12:40:21 by jnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "libft.h"


void	error_exit(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(1);
}

void	send_char(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c >> bit) & 1)
		{
			if (kill(pid, SIGUSR2) == -1)
				error_exit("Error: failed to send SIGURSR2\n");
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				error_exit("Error: failed to send SIGURSR1\n");
		}
		bit++;
		usleep(100);
	}
}

void send_string(int pid, const char *str)
{
	while(*str)
	{
		send_char(pid, *str);
		str++;
	}
	send_char(pid, '\0');
}

char *insert_separators(const char *str)
{
	size_t len;
	char *res;

	len = ft_strlen(str);
	res = malloc(len + len / SIZE + 2);
	if (!res) 
		return NULL;
	size_t i;
	size_t j;
	size_t count;
	i = 0;
	j = 0;
	count = 0;
	while(i < len)
	{
		res[j++] = str[i++];
		count++;
		if (count == SIZE)
		{
			res[j++] = '|';
			count = 0;
		}
	}
	res[j] = '\0';
	return (res);
}
