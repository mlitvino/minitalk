/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:21:38 by mlitvino          #+#    #+#             */
/*   Updated: 2024/12/24 14:30:03 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t bit = 0;

char	*get_bit(char *str, long int *bitlen, int len)
{
	if (bit)
		str[(*bitlen - 64) / 8] |= (1 << (7 - (*bitlen - 64) % 8));
	else
		str[(*bitlen - 64) / 8] &= ~(1 << (7 - (*bitlen - 64) % 8));
	(*bitlen)++;
	return (str);
}

void	get_len(long int *bitlen, int *len, char **str)
{
	if (bit)
		*len |= (1 << (31 - *bitlen - 32));
	else
		*len &= ~(1 << (31 - *bitlen - 32));
	(*bitlen)++;
	printf("LEN %d\n", *len);
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

void	get_clnt_pid(long int *bitlen, pid_t *client_pid)
{
	if (bit)
		*client_pid |= (1 << (31 - *bitlen));
	else
		*client_pid &= ~(1 << (31 - *bitlen));
	(*bitlen)++;
}

void	sig_handler(int sig)
{
	static long	int bitlen;
	static int 		len;
	static char		*str;
	static pid_t	clnt_pid;

	if (sig == SIGUSR1)
		bit = 1;
	else
		bit = 0;
	if (bitlen >= 64)
		str = get_bit(str, &bitlen, len);
	else if (bitlen < 32)
		get_clnt_pid(&bitlen, &clnt_pid);
	else if (bitlen < 64)
		get_len(&bitlen, &len, &str);
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

int	main(void)
{
	printf("Server PID: %d\n", getpid());
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	while (1)
		usleep(1);
	return (0);
}
