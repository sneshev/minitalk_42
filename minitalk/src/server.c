#include "minitalk.h"

int	main(void)
{
    struct signation sa;

	printf("Server PID: %d\n", getpid()); // must be ft_ !   !   !

    if (signation(SIGUSR1, &sa, NULL) == -1)
        write(1, "ERROR REVEIVING SIGUSR1\n", 24)
    if (signation(SIGUSR2, &sa, NULL) == -1)
        write(1, "ERROR REVEIVING SIGUSR2\n", 24)

	while (1)
		pause();
}