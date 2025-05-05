


void	send_char(pid_t server_pid, char c)
{
    int bit;

    bit = 7;
    while (bit >= 0)
    {
	    if ((c >> bit) & 1)
	    	kill(server_pid, SIGUSR2);
	    else
	    	kill(server_pid, SIGUSR1);
	    usleep(100);
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
    while (argv[2][i])
    {
        send_char(server_pid, argv[2][i]);
        i++;
    }
    send_char(server_pid, '\0');
}