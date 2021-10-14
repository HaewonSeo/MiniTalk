/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 20:20:17 by haseo             #+#    #+#             */
/*   Updated: 2021/10/15 02:24:07 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_msg(int server_pid, char *msg)
{
	int	i;
	int	j;

	i = -1;
	while (1)
	{
		++i;
		j = -1;
		while (++j < 8)
		{
			if (msg[i] & (1 << (7 - j)))
				kill(server_pid, SIGUSR2);
			else
				kill(server_pid, SIGUSR1);
			usleep(100);
		}
		if (!msg[i])
			break ;
	}
}

int	main(int argc, char *argv[])
{
	pid_t				server_pid;

	if (argc != 3 || !argv[2])
		ft_exit("[Usage] ./client [Server PID] [Message]\n");
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
		ft_exit("[Error] Invalid Server PID\n");
	ft_printf("[Client %d]>%s\n", getpid(), argv[2]);
	send_msg(server_pid, argv[2]);
	return (0);
}
