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
            kill(server_pid, SIGUSR2);
        else
            kill(server_pid, SIGUSR1);
        place--;
        while (!answer)
            pause();
    }
}

int main(int argc, char **argv)
{
    char *message;

	if (argc != 3)
		return (1);

	pid_t server_pid = (pid_t)ft_atoi(argv[1]);
	
    signal(SIGUSR1, handle_ack);

    message = argv[2];
    while (*message)
	{
        send_char(server_pid, *message);
        message++;
    }	
	return (0);
}
