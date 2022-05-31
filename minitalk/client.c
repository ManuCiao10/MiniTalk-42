/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eardingh <eardingh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:14:42 by eardingh          #+#    #+#             */
/*   Updated: 2022/05/31 14:59:14 by eardingh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s && fd)
		write(fd, s, ft_strlen(s));
}

int	ft_atoi(const char *str)
{
	int	i;
	int	num;
	int	sign;

	num = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num * sign);
}

//to send bit by bit a char
//Right shift is = divide number by two

void	send_signal(int pid, int c)
{
	int	j;
	int	ret;

	j = 0;
	while (j < 8)
	{
		usleep(75);
		if (c & (1 << j))
		{
			ret = kill(pid, SIGUSR1);
		}
		else
		{
			ret = kill(pid, SIGUSR2);
		}
		if (ret == -1)
		{
			ft_putstr_fd("error kill return", 2);
			exit(EXIT_FAILURE);
		}
		j++;
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	i = 0;
	if (argc != 3)
	{
		ft_putstr_fd("Missing arguments", 2);
		exit(EXIT_FAILURE);
	}
	pid = ft_atoi(argv[1]);
	while (argv[2][i])
	{
		send_signal(pid, argv[2][i]);
		i++;
	}
	send_signal(pid, argv[2][i]);
	exit(EXIT_SUCCESS);
}

/* The server must be started first. After its launch, it has to print its PID.
• The client takes two parameters:
	-The server PID.
 	-The string to send.
• The client must send the string passed as a parameter to the server.
Once the string has been received, the server must print it.
*/
