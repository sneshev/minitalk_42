/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:57:02 by sneshev           #+#    #+#             */
/*   Updated: 2025/05/07 15:59:20 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putstr_fd(const char *str, int fd)
{
	while (str && *str)
	{
		write(fd, str, 1);
		str++;
	}
}

static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static unsigned char	chr = 0;
	static int				bits = 0;

	(void)context;
	if (sig == SIGUSR2)
		chr |= (1 << (7 - bits));
	bits++;
	if (bits == 8)
	{
		write(1, &chr, 1);
		chr = 0;
		bits = 0;
	}
	usleep(50);
	if (kill(info->si_pid, SIGUSR1))
		ft_putstr_fd("ERROR: kill (server)", 1);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	if (sigemptyset(&sa.sa_mask) == -1)
		ft_putstr_fd("ERROR: sigemptyset (server)", 1);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		ft_putstr_fd("ERROR: sigaction (server)", 1);
	if (sigaction(SIGUSR2, &sa, NULL) == -1)
		ft_putstr_fd("ERROR: sigaction (server)", 1);
	printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
