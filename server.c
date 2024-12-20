/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 14:21:38 by mlitvino          #+#    #+#             */
/*   Updated: 2024/12/20 18:18:41 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile int bit = 0;

void	get_bit(char *str, int *len_inbit, int size)
{
	if (!str)
		{
			str = malloc(sizeof(char) * size + 1);
			if (!str)
				exit(1);
		}
	str[*len_inbit / 8] |= (1 << (7 - *len_inbit % 8));
}

int	get_size(int *len)
{

}

int	get_client_pid(int *len, pid_t *client_pid)
{

}

void	sig_handler(int sig)
{
	static long int	len_inbit;
	static int		size;
	static char		*str;
	static pid_t	clnt_pid;

	if (sig == SIGUSR1)
		bit = 1;
	else
		bit = 0;
	if (len_inbit < sizeof(int))
		get_clnt_pid(&len_inbit, &clnt_pid);
	else if (len_inbit < sizeof(int) * 2)
		get_size(&len_inbit);
	else if (len_inbit < size * 8)
		get_bit(str, &len_inbit, size);
	else
	{
		kill(clnt_pid, SIGUSR1);
		printf("%s", str);
		free(str);
		str = NULL;
		len_inbit = 0;
		size = 0;
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
