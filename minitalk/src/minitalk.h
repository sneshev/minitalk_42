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


#endif