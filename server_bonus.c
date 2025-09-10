/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:20:15 by marvin            #+#    #+#             */
/*   Updated: 2025/09/08 10:20:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minitalk_bonus.h"

t_server_state g_state;

static void flush_buffer(void)
{
    if (g_state.idx > 0)
    {
        g_state.buffer[g_state.idx] = '\0';
        ft_putstr_fd(g_state.buffer, 1);
        ft_putchar_fd('\n', 1);
        g_state.idx = 0;
    }
}

static void handle_char(unsigned char c)
{
    if (c == '\0')
    {
        flush_buffer();
    }
    else
    {
        if (g_state.idx < BUFFER_SIZE - 1)
        {
            g_state.buffer[g_state.idx++] = c;
        }
        else
        {
            flush_buffer();
            g_state.buffer[g_state.idx++] = c;
        }
    }
}

static void handle_signal(int sig, siginfo_t *info, void *context)
{
    (void)context;
    pid_t client_pid = info->si_pid;

    if (sig == SIGUSR2)
        g_state.c |= (1 << g_state.bit);

    g_state.bit++;

    if (g_state.bit == 8)
    {
        handle_char(g_state.c);
        g_state.c = 0;
        g_state.bit = 0;

        // envia ACK para o cliente
        if (kill(client_pid, SIGUSR1) == -1)
        {
            ft_putstr_fd("Erro ao enviar ACK\n", 2);
            exit(1);
        }
    }
}

int main (void)
{
    struct sigaction sa;
    sa.sa_sigaction = &handle_signal;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

    ft_putstr_fd("Server PID: ", 1);
    ft_putnbr_fd(getpid(), 1);
    ft_putchar_fd('\n', 1);

    if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
    {
        ft_putstr_fd("Erro ao configurar sinais\n", 2);
        return (1);
    }
    

    while(1)
        pause();    
}