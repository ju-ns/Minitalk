/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 21:01:54 by marvin            #+#    #+#             */
/*   Updated: 2025/09/11 21:01:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"
#include "libft.h"

static t_state g_state = {0, 0, 0};

static void	reset_state(void)
{
	g_state.bit = 0;
	g_state.c = 0;
}

static void	handle_char(void)
{
	if (g_state.c == '\0')
	{
		ft_putchar_fd('\n', 1);
		kill(g_state.client_pid, SIGUSR1);
	}
	else
		ft_putchar_fd(g_state.c, 1);
	reset_state();
}

static void	handle_signal(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (g_state.client_pid == 0)
		g_state.client_pid = info->si_pid;
	if (sig == SIGUSR2)
        g_state.c |= (1 << g_state.bit);
	g_state.bit++;
	if (g_state.bit == 8)
		handle_char();
	kill(g_state.client_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction sa;

	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handle_signal;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}
