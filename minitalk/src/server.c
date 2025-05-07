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

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == 2147483647)
		write(fd, "2147483647", 10);
	else if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			n *= -1;
			write(fd, "-", 1);
		}
		if (n > 9)
			ft_putnbr_fd(n / 10, fd);
		c = (n % 10) + '0';
		write (fd, &c, 1);
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
	ft_putstr_fd("Server pid: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	while (1)
		pause();
	return (0);
}
