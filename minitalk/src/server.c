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

void set_bit(t_server *server, int sig)
{
    if (sig == SIGUSR2)
    {
    if (server->bit_count == 0)
        server->curr_char |= (1 << 7);
    if (server->bit_count == 1)
        server->curr_char |= (1 << 6);
    if (server->bit_count == 2)
        server->curr_char |= (1 << 5);
    if (server->bit_count == 3)
        server->curr_char |= (1 << 4);
    if (server->bit_count == 4)
        server->curr_char |= (1 << 3);
    if (server->bit_count == 5)
        server->curr_char |= (1 << 2);
    if (server->bit_count == 6)
        server->curr_char |= (1 << 1);
    if (server->bit_count == 7)
        server->curr_char |= (1 << 0);
    }
}

void handle_signal(int sig, siginfo_t *info, void *context)
{
    static t_server server = {0, 0};
    (void)info;
    (void)context;

    set_bit(&server, sig);
    server.bit_count += 1;
    if (server.bit_count == 8)
    {
        write(1, &server.curr_char, 1);
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