/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 13:06:01 by mlitvino          #+#    #+#             */
/*   Updated: 2024/12/20 13:06:01 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// void	sig_handler(int sig)
// {
// 	if (sig == SIGUSR1)
// 		printf("Message delivered successfully!\n");
// }

// void	send_pid(pid_t *serv_pid, pid_t *clnt_pid)
// {
// 	unsigned int i;

// 	i = 0;
// 	// printf("CLIENT PID : %d\n", *clnt_pid); // DEL
// 	while (i < (int)sizeof(int) * 8)
// 	{
// 		if (*clnt_pid & (1 << (31 - i)))
// 			kill(*serv_pid, SIGUSR1);
// 		else
// 			kill(*serv_pid, SIGUSR2);
// 		i++;
// 		usleep(1000);
// 	}
// }

// void	send_len(pid_t *serv_pid, int *len)
// {
// 	int i;

// 	i = 0;
// 	// printf("CLIENT LEN : %d\n", *len); // DEL
// 	while (i < 32)
// 	{
// 		if (*len & (1 << (31 - i)))
// 			kill(*serv_pid, SIGUSR1);
// 		else
// 			kill(*serv_pid, SIGUSR2);
// 		i++;
// 		usleep(1000);
// 	}
// }

// void	send_str(pid_t *serv_pid, char *str, int *len)
// {
// 	int i;

// 	i = 0;
// 	printf("CLIENT STR: %s\n", str);// DEL
// 	while (i < *len * 8)
// 	{
// 		if (str[i / 8] & (1 << (7 - i % 8)))
// 			kill(*serv_pid, SIGUSR1);
// 		else
// 			kill(*serv_pid, SIGUSR2);
// 		i++;
// 		usleep(1000);
// 	}
// }

// int	main(int argc, char *argv[])
// {
// 	pid_t	clnt_pid;
// 	pid_t	serv_pid;
// 	int		len;

// 	if (argc != 3)
// 	{
// 		printf("Wrong format: <pid> <message>\n");
// 		return (1);
// 	}
// 	signal(SIGUSR1, sig_handler);
// 	clnt_pid = getpid();
// 	serv_pid = atoi(argv[1]);
// 	len = strlen(argv[2]);
// 	send_pid(&serv_pid, &clnt_pid);
// 	send_len(&serv_pid, &len);
// 	send_str(&serv_pid, argv[2], &len);
// 	usleep(1000);
// 	return (0);
// }

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

volatile int signal_received = 0;

void sig_handler(int sig)
{
    if (sig == SIGUSR1)
    {
        signal_received = 1;
        printf("Message delivered successfully!\n");
    }
}

void send_pid(pid_t *serv_pid, pid_t *clnt_pid)
{
    unsigned int i = 0;
    while (i < (int)sizeof(int) * 8)
    {
        if (*clnt_pid & (1 << (31 - i)))
            kill(*serv_pid, SIGUSR1);
        else
            kill(*serv_pid, SIGUSR2);
        i++;
        usleep(5000);
    }
}

void send_len(pid_t *serv_pid, int *len)
{
    int i = 0;
    while (i < 32)
    {
        if (*len & (1 << (31 - i)))
            kill(*serv_pid, SIGUSR1);
        else
            kill(*serv_pid, SIGUSR2);
        i++;
        pause();
    }
}

void send_str(pid_t *serv_pid, char *str, int *len)
{
    int i = 0;
    while (i < *len * 8)
    {
        if (str[i / 8] & (1 << (7 - i % 8)))
            kill(*serv_pid, SIGUSR1);
        else
            kill(*serv_pid, SIGUSR2);
        i++;
        pause();
        usleep(100);
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
        printf("Wrong format: <pid> <message>\n");
        return 1;
    }

    signal(SIGUSR1, sig_handler);
    signal(SIGUSR2, sig_handler);
    clnt_pid = getpid();
    serv_pid = atoi(argv[1]);
    len = strlen(argv[2]);

    // Start time counting
    gettimeofday(&start_time, NULL);

    send_pid(&serv_pid, &clnt_pid);
    send_len(&serv_pid, &len);
	printf("CLIENT LEN : %d\n", len); // DEL
    send_str(&serv_pid, argv[2], &len);

    // Wait for signal to be received
    while (!signal_received)
        pause();

    // End time counting
    gettimeofday(&end_time, NULL);

    // Calculate elapsed time in milliseconds
    elapsed_time = (end_time.tv_sec - start_time.tv_sec) * 1000;
    elapsed_time += (end_time.tv_usec - start_time.tv_usec) / 1000;

    printf("Time taken: %ld ms\n", elapsed_time);
    return 0;
}
