/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:26:51 by mlitvino          #+#    #+#             */
/*   Updated: 2025/02/26 12:52:34 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# define _POSIX_C_SOURCE 200000L
# include <signal.h>
# include <sys/types.h>
# include "libft.h"
# define INT_BITS 32

void	send_len(pid_t *serv_pid, int *len);
void	send_str(pid_t *serv_pid, char *str, int *len);

void	get_clnt_pid(long int *bitlen, pid_t *client_pid, int sig);
char	*get_len(long int *bitlen, int *len, char *str, int sig);
char	*get_bit(char *str, long int *bitlen, int sig);

#endif
