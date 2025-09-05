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

#include "../includes/minitalk.h"
#include "../libft/libft.h"

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
