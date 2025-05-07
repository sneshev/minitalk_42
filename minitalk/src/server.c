#include "minitalk.h"

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

char set_bit( char curr_char, int bit_count, int sig)
{
    if (sig == SIGUSR2)
        curr_char |= 0x80 >> bit_count;
    // if(bit_count == 7 )
    //     write(1, &curr_char, 1);
    return curr_char;
}

void handle_signal(int sig, siginfo_t *info, void *context)
{
    static t_server server = {0, 0};
    (void)context;

    server.curr_char = set_bit(server.curr_char, server.bit_count, sig);
    server.bit_count += 1;
    if (server.bit_count == 8)
    {
        write(1, &server.curr_char, 1);
        if (info && info->si_pid != 0)
            kill(info->si_pid, SIGUSR1);
        server.bit_count = 0;
        server.curr_char = 0;

    }
}

int	main(void)
{
    struct sigaction sa;

    write(1, "Server PID: ", 12);
    ft_putnbr_fd(getpid(), 1);
    write(1, "\n", 1);

    sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1)
    {
        write(1, "ERROR REVEIVING SIGUSR1\n", 24);
    }
    if (sigaction(SIGUSR2, &sa, NULL) == -1)
    {
        write(1, "ERROR REVEIVING SIGUSR2\n", 24);
    }

	while (1)
		pause();
}