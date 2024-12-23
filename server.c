/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:21:38 by mlitvino          #+#    #+#             */
/*   Updated: 2024/12/23 19:36:02 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t bit = 0;

char	*get_bit(char *str, long int *bitlen, int len)
{

    long int byte_index = (*bitlen - 64) / 8;   // Byte index
    long int bit_index = 7 - ((*bitlen - 64) % 8);

	//printf("GET_BIT\n"); // DEL
	if (!str)
		{
			str = malloc(sizeof(char) * len + 1);
			if (!str)
				exit(1);
			bzero(str, len + 1);
			str[len] = 0;
		}
    if (bit) {
        str[byte_index] |= (1 << bit_index); // Set the bit
    } else {
        str[byte_index] &= ~(1 << bit_index); // Clear the bit
    }
	// if (bit)
	// 	str[(*bitlen - 64) / 8] |= (1 << (7 - *bitlen - 64));
	// else
	// 	str[(*bitlen - 64) / 8] &= ~(1 << (7 - *bitlen - 64));
	(*bitlen)++;
	//printf("STR: %s\n", str); // DEL
	return (str);
}

void	get_len(long int *bitlen, int *len)
{
	//printf("GET_LEN\n"); // DEL
	if (bit)
		*len |= (1 << (31 - *bitlen - 32));
	else
		*len &= ~(1 << (31 - *bitlen - 32));
	(*bitlen)++;
	//printf("LEN: %d\n", *len); // DEL
}

void	get_clnt_pid(long int *bitlen, pid_t *client_pid)
{
	//printf("GET_PID\n"); // DEL
	if (bit)
		*client_pid |= (1 << (31 - *bitlen));
	else
		*client_pid &= ~(1 << (31 - *bitlen));
	(*bitlen)++;
	//printf("PID: %d\n", *client_pid); // DEL
}

void	sig_handler(int sig)
{
	static long	int bitlen;
	static int 		len;
	static char		*str;
	static pid_t	clnt_pid;

	// if (bitlen > 62)
	// {
	// 	printf("Signal received: %d\n", sig); // DEL
	// 	printf("bitlen: %lu\n", bitlen); // DEL
	// }
	if (sig == SIGUSR1)
		bit = 1;
	else
		bit = 0;
	if (bitlen < 32)
		get_clnt_pid(&bitlen, &clnt_pid);
	else if (bitlen < 64)
		get_len(&bitlen, &len);
	else if (bitlen - 64 < len * 8)
	{
		str = get_bit(str, &bitlen, len);
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

int	main(void)
{
	printf("Server PID: %d\n", getpid());
	signal(SIGUSR1, sig_handler);
	signal(SIGUSR2, sig_handler);
	while (1)
		pause();
	return (0);
}
