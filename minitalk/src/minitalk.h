#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h> 

typedef struct s_server
{
	volatile sig_atomic_t bit_count;
	volatile sig_atomic_t curr_char;
}	t_server;


// Optionally you can define utility prototypes here too, like:


// void	send_char(pid_t pid, char c);


// void	handle_signal(int sig, siginfo_t *info, void *context);

#endif