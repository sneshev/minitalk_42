#include "minitalk.h"

volatile sig_atomic_t answer = 0;

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

void handle_ack(int sig)
{
	(void)sig;
	answer = 1;
}


void send_char(pid_t server_pid, unsigned char chr)
{
    int place;
    int bit_value;

    place = 7;
    while(place >= 0)
    {
        answer = 0;
        bit_value = chr >> place & 1;
		if (bit_value == 1)
		{
            if (kill(server_pid, SIGUSR2))
				write(1, "ERROR", 5);;
		}
        else
		{
            if (kill(server_pid, SIGUSR1))
				write(1, "ERROR", 5);;
		}
        place--;
        while (!answer)
            pause();
		usleep(50);
    }
}

int main(int argc, char **argv)
{
    char *message;
	int i;

	if (argc != 3)
		return (1);

	pid_t server_pid = (pid_t)ft_atoi(argv[1]);
	
	struct sigaction sa;
	sa.sa_handler = handle_ack;
	sa.sa_flags = SA_RESTART;
	if (sigemptyset(&sa.sa_mask) == -1)
		perror("sigemptyset");
	if (sigaction(SIGUSR1, &sa, NULL) == -1)
		perror("sigaction");
	

	i = 0;
    message = argv[2];
    while (*message)
	{
        send_char(server_pid, *message);
        i++;
        message++;
		// if (i % 101 == 0)
		// 	usleep(99999);
    }	
	return (0);
}