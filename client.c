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

void	sig_handler(int sig)
{
	printf("Message delivered successfully!");
}

int	strsize(char *str)
{
	int	size;

	size = 0;
	while(str[size])
		size++;
	return (++size);
}

void	send_pid()
{

}

void	send_size()
{

}

void	send_str()
{

}

int	main(int argc, char *argv[])
{
	pid_t	clnt_pid;
	pid_t	serv_pid;
	int		size;

	if (argc != 3)
	{
		printf("Wrong format: <pid> <message>\n");
		return (1);
	}
	signal(SIGUSR1, sig_handler);
	clnt_pid = getpid();
	serv_pid = atoi(argv[1]);
	size = strsize(argv[2]);
	sent_pid(clnt_pid);
	send_size(size);
	send_str(argv[2]);
	return (0);
}
