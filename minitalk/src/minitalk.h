#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h> 

typedef struct s_server
{
	volatile sig_atomic_t bit_count;
	char  curr_char;
}	t_server;

void	ft_putnbr_fd(int n, int fd);
int		ft_atoi(const char *nptr);


#endif

//    write(1, "Server PID: ", 12);
// ft_putnbr_fd(getpid(), 1);
// write(1, "\n", 1);