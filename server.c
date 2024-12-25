/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:21:38 by mlitvino          #+#    #+#             */
/*   Updated: 2024/12/25 16:41:58 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t usr_sig = 0;

static inline char	*get_bit(char *str, long int *bitlen, int sig, pid_t *clnt_pid)
{
	if (sig == SIGUSR1)
		str[(*bitlen - 64) / 8] |= (1 << (7 - (*bitlen - 64) % 8));
	else
		str[(*bitlen - 64) / 8] &= ~(1 << (7 - (*bitlen - 64) % 8));
	(*bitlen)++;
	kill(*clnt_pid, SIGUSR2);
	return (str);
}

void	get_len(long int *bitlen, int *len, char **str, int sig)
{
	if (sig == SIGUSR1)
		*len |= (1 << (31 - *bitlen - 32));
	else
		*len &= ~(1 << (31 - *bitlen - 32));
	(*bitlen)++;
	//printf("LEN %d\n", *len);
	if (*bitlen == 64)
	{
		*str = malloc((size_t)*len + 1);
		if (!*str)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		(*str)[*len] = 0;
	}
}

void	get_clnt_pid(volatile long int *bitlen, pid_t *client_pid, int sig)
{
	if (sig == SIGUSR1)
		*client_pid |= (1 << (31 - *bitlen));
	else
		*client_pid &= ~(1 << (31 - *bitlen));
	(*bitlen)++;
}

static inline void	proceed_signal(int sig)
{
	static long	int bitlen;
	static int 		len;
	static char		*str;
	static pid_t	clnt_pid;

	if (bitlen >= 64)
		str = get_bit(str, &bitlen, sig, &clnt_pid);
	else if (bitlen < 32)
		get_clnt_pid(&bitlen, &clnt_pid, sig);
	else if (bitlen < 64)
	{
		get_len(&bitlen, &len, &str, sig);
		kill(clnt_pid, SIGUSR2);
	}
	if (bitlen - 64 == len * 8)
	{
		kill(clnt_pid, SIGUSR1);
		printf("RESULT: %s\n", str);
		free(str);
		str = NULL;
		bitlen = 0;
		len = 0;
		clnt_pid = 0;
	}
}

void	sig_handler(int sig)
{
	usr_sig = sig;
}

int	main(void)
{
	struct sigaction sa;

	sa.sa_handler = sig_handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	printf("Server PID: %d\n", getpid());
	while (1)
	{
		pause();
		proceed_signal(usr_sig);
	}
	return (0);
}
