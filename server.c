/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:21:38 by mlitvino          #+#    #+#             */
/*   Updated: 2024/12/27 18:34:34 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t	g_usr_sig = -1;

char	*get_bit(char *str, long int *bitlen, int sig)
{
	if (sig == SIGUSR1)
		str[(*bitlen - 64) / 8] |= (1 << (7 - (*bitlen - 64) % 8));
	else
		str[(*bitlen - 64) / 8] &= ~(1 << (7 - (*bitlen - 64) % 8));
	(*bitlen)++;
	return (str);
}

char	*get_len(long int *bitlen, int *len, char *str, int sig)
{
	if (sig == SIGUSR1)
		*len |= (1 << (31 - *bitlen - 32));
	else
		*len &= ~(1 << (31 - *bitlen - 32));
	(*bitlen)++;
	if (*bitlen == 64)
	{
		str = malloc(*len + 1);
		if (!str)
			exit(EXIT_FAILURE);
		str[*len] = 0;
	}
	return (str);
}

void	get_clnt_pid(long int *bitlen, pid_t *client_pid, int sig)
{
	if (sig == SIGUSR1)
		*client_pid |= (1 << (31 - *bitlen));
	else
		*client_pid &= ~(1 << (31 - *bitlen));
	(*bitlen)++;
}

void	sig_handler(int sig)
{
	static long int	bitlen;
	static int		len;
	static char		*str;
	static pid_t	clnt_pid;

	if (bitlen >= 64 && bitlen - 64 != len * 8)
		str = get_bit(str, &bitlen, sig);
	else if (bitlen < 32)
		get_clnt_pid(&bitlen, &clnt_pid, sig);
	else if (bitlen < 64)
		str = get_len(&bitlen, &len, str, sig);
	else
	{
		kill(clnt_pid, SIGUSR1);
		ft_printf("RESULT: %s\n", str);
		free(str);
		str = NULL;
		bitlen = 0;
		len = 0;
		clnt_pid = 0;
	}
	if (bitlen >= 32)
		kill(clnt_pid, SIGUSR2);
}

int	main(void)
{
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	ft_printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
