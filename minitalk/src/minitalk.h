/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:59:32 by sneshev           #+#    #+#             */
/*   Updated: 2025/05/07 15:59:51 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h> 

typedef struct s_server
{
	volatile sig_atomic_t	bit_count;
	char					curr_char;
}	t_server;

void	ft_putnbr_fd(int n, int fd);
int		ft_atoi(const char *nptr);
void	ft_putstr_fd(const char *str, int fd);

#endif

//    write(1, "Server PID: ", 12);
// ft_putnbr_fd(getpid(), 1);
// write(1, "\n", 1);