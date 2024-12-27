/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 13:06:01 by mlitvino          #+#    #+#             */
/*   Updated: 2024/12/27 18:31:53 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile int signal_received = 0;

void sig_handler(int sig)
{
	if (sig == SIGUSR1)
	{
		signal_received = 1;
		ft_printf("\nMessage delivered successfully!\n");
	}
	else if (sig == SIGUSR2)
		{ }
}

void send_pid(pid_t *serv_pid, pid_t *clnt_pid)
{
	int i;

	i = 0;
	while (i < (int)sizeof(int) * 8)
	{
		if (*clnt_pid & (1 << ((int)sizeof(int) * 8 - 1 - i)))
			kill(*serv_pid, SIGUSR1);
		else
			kill(*serv_pid, SIGUSR2);
		usleep(400);
		i++;
	}
}

void send_len(pid_t *serv_pid, int *len)
{
	int i;

	i = 0;
	while (i < (int)sizeof(int) * 8)
	{
		if (*len & (1 << ((int)sizeof(int) * 8 - 1 - i)))
			kill(*serv_pid, SIGUSR1);
		else
			kill(*serv_pid, SIGUSR2);
		usleep(4000);
		i++;
	}
}

void send_str(pid_t *serv_pid, char *str, int *len)
{
	int i;

	i = 0;
	while (i < *len * 8 + 1)
	{
		if (str[i / 8] & (1 << (7 - i % 8)))
			kill(*serv_pid, SIGUSR1);
		else
			kill(*serv_pid, SIGUSR2);
		usleep(4000);
		i++;
	}
}

int main(int argc, char *argv[])
{
	pid_t clnt_pid;
	pid_t serv_pid;
	int len;
	struct timeval start_time, end_time;
	long elapsed_time;

	if (argc != 3)
	{
		ft_printf("Wrong format: <pid> <message>\n");
		return 1;
	}
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	clnt_pid = getpid();
	serv_pid = ft_atoi(argv[1]);
	len = ft_strlen(argv[2]);

	gettimeofday(&start_time, NULL);

	send_pid(&serv_pid, &clnt_pid);
	send_len(&serv_pid, &len);
	send_str(&serv_pid, argv[2], &len);

	while (!signal_received)
		usleep(1);

	gettimeofday(&end_time, NULL);
	elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000;
	elapsed_time += (end_time.tv_usec - start_time.tv_usec) / 1000;
	ft_printf("CLIENT LEN : %d\n", len);
	ft_printf("CL PID: %d\n", clnt_pid);
	ft_printf("SV PID: %d\n", serv_pid);
	ft_printf("\nTime taken: %d ms\n", elapsed_time);
	return 0;
}
