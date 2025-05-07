#include "minitalk.h"


static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static unsigned char chr = 0;
	static int bits = 0;

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
		write(1, "ERROR", 5);
}

int main(void)
{
	struct sigaction sa;

	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	if (sigemptyset(&sa.sa_mask) == -1)
	    perror("sigemptyset");

	if (sigaction(SIGUSR1, &sa, NULL) == -1)
	    perror("sigaction SIGUSR1");

	if (sigaction(SIGUSR2, &sa, NULL) == -1)
	    perror("sigaction SIGUSR2");
	
	printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}