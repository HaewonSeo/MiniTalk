/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haseo <haseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 20:20:14 by haseo             #+#    #+#             */
/*   Updated: 2021/10/14 02:02:05 by haseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void ft_sigaction(int sig, siginfo_t *info, void *ucontext)
{
	static int				client_pid;
	static int				i;
	static unsigned char	ch;

	(void)ucontext;
	if (sig != SIGUSR1 && sig != SIGUSR2)
	 	return ;
	if (!client_pid)
	{
		client_pid = info->si_pid;
		ft_printf("[Client %d]>", client_pid);
	}
	ch = (ch << 1) | (sig == SIGUSR2);
	if (++i == 8)
	{
		i = 0;
		if (ch == '\0')
		{
			ft_putchar_fd('\n', STDOUT_FILENO);
			//kill(client_pid, SIGUSR1);
			client_pid = 0;
			return ;
		}
		ft_putchar_fd(ch, STDOUT_FILENO);
		//kill(client_pid, SIGUSR2);
		ch = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("[Server %d]\n", getpid());
	sa.sa_sigaction = ft_sigaction;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
