/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:55:56 by sneshev           #+#    #+#             */
/*   Updated: 2025/05/07 15:56:47 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_answer = 0;

void	ft_putstr_fd(const char *str, int fd)
{
	while (str && *str)
	{
		write(fd, str, 1);
		str++;
	}
}

int	ft_atoi(const char *nptr)
{
	int	sign;
	int	nbr;

	nbr = 0;
	sign = 1;
	while (*nptr == 32 || (*nptr > 8 && *nptr < 14))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		nbr += *nptr - '0';
		if (*(nptr + 1) >= '0' && *(nptr + 1) <= '9')
			nbr *= 10;
		nptr++;
	}
	return (nbr * sign);
}

void	handle_ack(int sig)
{
	(void)sig;
	g_answer = 1;
}

void	send_char(pid_t server_pid, unsigned char chr)
{
	int	place;
	int	bit_value;

	place = 7;
	while (place >= 0)
	{
		g_answer = 0;
		bit_value = chr >> place & 1;
		if (bit_value == 1)
		{
			if (kill(server_pid, SIGUSR2))
				ft_putstr_fd("ERROR: kill (client)", 1);
		}
		else
		{
			if (kill(server_pid, SIGUSR1))
				ft_putstr_fd("ERROR: kill (client)", 1);
		}
		place--;
		while (!g_answer)
			pause();
		usleep(50);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	char				*message;
	pid_t				server_pid;

	if (argc != 3)
		return (1);
	server_pid = (pid_t)ft_atoi(argv[1]);
	sa.sa_handler = handle_ack;
	sa.sa_flags = SA_RESTART;
	if (sigemptyset(&sa.sa_mask) == -1)
		ft_putstr_fd("ERROR: segemptyset (client)", 1);
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		ft_putstr_fd("ERROR: sigaction (client)", 1);
	message = argv[2];
	while (*message)
	{
		send_char(server_pid, *message);
		message++;
	}
	return (0);
}
