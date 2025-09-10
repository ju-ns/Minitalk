/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:39:10 by marvin            #+#    #+#             */
/*   Updated: 2025/09/08 10:39:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"
#include "libft.h"

static volatile int ack_received = 0;

void ack_handler(int sig)
{
    (void)sig;
    ack_received = 1;

}

static void send_char(int pid, unsigned char c)
{
    int bit = 0;

    while (bit < 8)
    {
        if ((c >> bit) & 1)
        {
            if (kill(pid, SIGUSR2) == -1)
                error_exit("Error: failed to send SIGUSR2\n");
        }
        else
        {
            if (kill(pid, SIGUSR1) == -1)
                error_exit("Error: failed to send SIGUSR1\n");
        }
        bit++;
        usleep(100);
    }

    ack_received = 0;
    while (!ack_received)
        pause();
}
void send_string(int pid, const char *str)
{
    unsigned char *ptr = (unsigned char *)str;
    while(*ptr)
        send_char(pid, *ptr++);
    send_char(pid, '\0');
}

int main(int argc, char **argv)
{
    int server_pid;
    char **chunks;
    int i;
    struct sigaction sa;

    if (argc != 3)
        return(ft_putstr_fd("Uso: ./client_bonus <PID> <mensagem>\n", 2), 1);
    server_pid = ft_atoi(argv[1]);
    if (server_pid <= 0)
        return(ft_putstr_fd("PID inválido\n", 2), 1);
    sa.sa_handler = ack_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGUSR1, &sa, NULL) == -1)
        ft_putstr_fd("Erro ao configurar ACK handler\n", 2);
    chunks = ft_split(argv[2], '\n');
    if (!chunks)
        return (1);
    i = 0;
    while (chunks[i])
        send_string(server_pid, chunks[i++]);
    free_split(chunks);
    return (0);
}

