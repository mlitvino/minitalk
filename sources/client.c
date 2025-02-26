/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 13:06:01 by mlitvino          #+#    #+#             */
/*   Updated: 2025/02/26 13:40:16 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

volatile sig_atomic_t	g_signal_received = 0;

void	sig_handler(int sig)
{
	if (SIGUSR1 == sig)
		g_signal_received = 1;
}

void	send_len(pid_t *serv_pid, int *len)
{
	int	i;

	i = 0;
	while (i < (int) sizeof(int) * 8)
	{
		if (*len & (1 << ((int) sizeof(int) * 8 - 1 - i)))
			kill(*serv_pid, SIGUSR1);
		else
			kill(*serv_pid, SIGUSR2);
		while (!g_signal_received)
			usleep(100);
		g_signal_received = 0;
		i++;
	}
}

void	send_str(pid_t *serv_pid, char *str, int *len)
{
	int	i;

	i = 0;
	while (i < *len * 8 + 1)
	{
		if (str[i / 8] & (1 << (7 - i % 8)))
			kill(*serv_pid, SIGUSR1);
		else
			kill(*serv_pid, SIGUSR2);
		while (!g_signal_received)
			usleep(100);
		g_signal_received = 0;
		i++;
	}
}

int	main(int argc, char *argv[])
{
	pid_t	serv_pid;
	int		len;

	if (argc != 3)
	{
		ft_printf("Wrong format: <pid> <message>\n");
		return (1);
	}
	signal(SIGUSR1, sig_handler);
	serv_pid = ft_atoi(argv[1]);
	len = ft_strlen(argv[2]);
	send_len(&serv_pid, &len);
	send_str(&serv_pid, argv[2], &len);
	ft_printf("Message delivered successfully!\n");
	return (0);
}
