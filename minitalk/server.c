/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eardingh <eardingh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:14:39 by eardingh          #+#    #+#             */
/*   Updated: 2022/05/31 15:00:49 by eardingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* The SA_SIGINFO flag tells sigaction() to use the 
sa_sigaction field, not sa_handler. */

// c = c | (1 << len)
//len --> to store the number of bits read
//char -> to store the character read

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putchar_fd('2', fd);
		ft_putnbr_fd(147483648, fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (n < 10)
		ft_putchar_fd(n + '0', fd);
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}

void	handler(int signal)
{
	static int	len = 0;
	static char	c = 0;

	if (signal == SIGUSR1)
	{
		c = c | (1 << len);
	}
	len++;
	if (len == 8)
	{
		write(1, &c, 1);
		if (c == '\0')
			write(1, "\n", 1);
		len = 0;
		c = 0;
	}
}

int	main(void)
{
	int					pid;

	pid = getpid();
	write(1, "PID:", 4);
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while (1)
		pause();
	return (0);
}

/* The server must be started first. After its launch, it has to print its PID.
• The client takes two parameters:
	-The server PID.
 	-The string to send.
• The client must send the string passed as a parameter to the server.
Once the string has been received, the server must print it.
*/
