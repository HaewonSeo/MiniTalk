/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 20:20:17 by haseo             #+#    #+#             */
/*   Updated: 2021/10/14 18:31:53 by haseo            ###   ########.fr       */
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

static void	ft_sigaction(int sig, siginfo_t *info, void *ucontext)
{
	static int	cnt;

	(void)ucontext;
	if (sig == SIGUSR2)
		++cnt;
	else if (sig == SIGUSR1)
	{
		ft_printf("[Server %d] Received %d Signals\n", info->si_pid, ++cnt);
		ft_exit(NULL);
	}
}

int	main(int argc, char *argv[])
{
	struct sigaction	sa;
	pid_t				server_pid;

	if (argc != 3 || !argv[2])
		ft_exit("[Usage] ./client [Server PID] [Message]\n");
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
		ft_exit("[Error] Invalid Server PID\n");
	ft_printf("[Client %d]>%s\n", getpid(), argv[2]);
	sa.sa_sigaction = ft_sigaction;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	send_msg(server_pid, argv[2]);
	while (1)
		pause();
	return (0);
}
