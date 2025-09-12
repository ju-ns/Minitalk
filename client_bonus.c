/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:02:22 by marvin            #+#    #+#             */
/*   Updated: 2025/09/11 21:02:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"
#include "libft.h"

static volatile sig_atomic_t g_ack = 0;

static void	ack_handler(int sig)
{
	(void)sig;
	g_ack = 1;
}

static void	send_char(pid_t server_pid, unsigned char c)
{
	int bit = 0;

	while (bit < 8)
	{
        g_ack = 0;
		if ((c >> bit) & 1)
            kill(server_pid, SIGUSR2);
		else
            kill(server_pid, SIGUSR1);
		bit++;
		while (!g_ack)
			pause();
	}
}

static void	send_chunk(pid_t server_pid, char *chunk, int len)
{
	int i = 0;

	while (i < len)
	{
		send_char(server_pid, (unsigned char)chunk[i]);
		i++;
	}
}

static void	send_message(pid_t server_pid, char *msg)
{
	int i = 0;
	int len = ft_strlen(msg);

	while (i < len)
	{
		int chunk_len = (len - i > CHUNK_SIZE) ? CHUNK_SIZE : len - i;
		send_chunk(server_pid, msg + i, chunk_len);
		i += chunk_len;
	}
	send_char(server_pid, '\0'); // fim da mensagem
}

int	main(int argc, char **argv)
{
	struct sigaction sa;
	pid_t server_pid;

	if (argc != 3)
	{
		ft_putstr_fd("Uso: ./client_bonus <PID> <mensagem>\n", 2);
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
	{
		ft_putstr_fd("PID inválido\n", 2);
		return (1);
	}
	sa.sa_handler = ack_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGUSR1, &sa, NULL);
	send_message(server_pid, argv[2]);
	return (0);
}
