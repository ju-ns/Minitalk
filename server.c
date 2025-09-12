/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnogueir <jnogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 11:10:47 by jnogueir          #+#    #+#             */
/*   Updated: 2025/09/05 13:39:47 by jnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "libft.h"

static void process_char(unsigned char c, char *buffer, int *idx)
{
	if(c == '\0')
	{
		buffer[*idx] = '\0';
		ft_putstr_fd(buffer, 1);
		ft_putchar_fd('\n', 1);
		*idx = 0;
	}
	else if (c == 4) //verificar
	{
		ft_putstr_fd("Encerrando servidor ...\n", 1);
		exit(0);
	}
	else
	{
		if(*idx < BUFFER_SIZE -  1)
			buffer[(*idx)++] = c;
		else
		{
			buffer[*idx] = '\0';
			ft_putstr_fd(buffer, 1);
			*idx = 0;
			buffer[(*idx)++] = c;
		}
	}
}

static void handle_signal(int sig, siginfo_t *info, void *context)
{
	static int bit = 0;
	static unsigned char c = 0;
	static char buffer[BUFFER_SIZE];
	static int idx = 0;
	(void) info;
	(void) context;
	if(sig == SIGUSR2) 
		c |= (1 << bit);
	bit++;
	if(bit == 8)
	{
		process_char(c, buffer, &idx);
		bit = 0;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	ft_putstr_fd("Server PID:", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		return (1);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		return (1);
	while (1)
		pause();
}
