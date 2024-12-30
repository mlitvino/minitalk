/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:26:51 by mlitvino          #+#    #+#             */
/*   Updated: 2024/12/30 13:02:09 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <signal.h>
# include <sys/types.h>
# include "libft.h"

void	send_pid(pid_t *serv_pid, pid_t *clnt_pid);
void	send_len(pid_t *serv_pid, int *len);
void	send_str(pid_t *serv_pid, char *str, int *len);

void	get_clnt_pid(long int *bitlen, pid_t *client_pid, int sig);
char	*get_len(long int *bitlen, int *len, char *str, int sig);
char	*get_bit(char *str, long int *bitlen, int sig);

void	sig_handler(int sig);

#endif

