#include "minitalk.h"

void set_bit(t_server *server, int sig)
{
    if (sig == SIGUSR1)
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

void handle_signal(int sig)
{
    static t_server server = {0, 0};  

    // write(1, "!!", 2);
    // if (sig == SIGUSR1)
    //     write(1, "SIGUSR1 received\n", 17);
    // if (sig == SIGUSR2)
    //     write(1, "SIGUSR2 received\n", 17);

    set_bit(&server, sig);

    server.bit_count++;

    if (server.bit_count == 8)
    {
        write(1, (const void *)&server.curr_char, 1); 
        write(1, "\n", 1); 
        server.bit_count = 0;
        server.curr_char = 0;
    }
}

int	main(void)
{
	printf("Server PID: %d\n", getpid());

    if (signal(SIGUSR1, handle_signal) == SIG_ERR)
	{
		write(1, "Error: Unable to catch SIGUSR1\n", 30);
		return 1;
	}
    if (signal(SIGUSR2, handle_signal) == SIG_ERR)
	{
		write(1, "Error: Unable to catch SIGUSR2\n", 30);
		return 1;
	}

	while (1)
		pause();
}