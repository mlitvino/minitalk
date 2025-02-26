/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:21:38 by mlitvino          #+#    #+#             */
/*   Updated: 2025/02/26 13:40:31 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

char	*get_bit(char *str, long int *bitlen, int sig)
{
	if (sig == SIGUSR1)
		str[(*bitlen - INT_BITS) / 8] |= (1 << (7 - (*bitlen - INT_BITS) % 8));
	else
		str[(*bitlen - INT_BITS) / 8] &= ~(1 << (7 - (*bitlen - INT_BITS) % 8));
	(*bitlen)++;
	return (str);
}

char	*get_len(long int *bitlen, int *len, char *str, int sig)
{
	if (sig == SIGUSR1)
		*len |= (1 << (31 - *bitlen));
	else
		*len &= ~(1 << (31 - *bitlen));
	(*bitlen)++;
	if (*bitlen == INT_BITS)
	{
		str = malloc(*len + 1);
		if (!str)
			exit(EXIT_FAILURE);
		str[*len] = 0;
	}
	return (str);
}

void	sig_handler(int sig, siginfo_t *info, void *context)
{
	static long int	bitlen;
	static int		len;
	static char		*str;

	(void)context;
	if (bitlen >= INT_BITS && bitlen - INT_BITS != len * 8)
		str = get_bit(str, &bitlen, sig);
	else if (bitlen < INT_BITS)
		str = get_len(&bitlen, &len, str, sig);
	else
	{
		ft_printf("CLIENT PID: %d\n", info->si_pid);
		ft_printf("MESSAGE: %s\n", str);
		free(str);
		str = NULL;
		bitlen = 0;
		len = 0;
	}
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = sig_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
