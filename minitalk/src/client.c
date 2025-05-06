#include "minitalk.h"

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

void	send_char(pid_t server_pid, char c)
{
    int bit;

    bit = 7;
    printf("char: %c\n", c);
    while (bit >= 0)
    {
	    if ((c >> bit) & 1)
	    {
            kill(server_pid, SIGUSR2);
            // printf("SIGUSR2 sent\n");
        }	
	    else
        {
	    	kill(server_pid, SIGUSR1);
            // printf("SIGUSR1 sent\n");
        }
	    usleep(600);
        bit--;
    }
}

int main(int argc, char *argv[])
{
    pid_t   server_pid;
    int     i;

    if (argc != 3)
    {
        return 0;
    }
    server_pid = (pid_t)ft_atoi(argv[1]);
    i = 0;
    while (argv[2][i])
    {
        send_char(server_pid, argv[2][i]);
        i++;
    }
    send_char(server_pid, '\0');
}