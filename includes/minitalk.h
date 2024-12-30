/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:26:51 by mlitvino          #+#    #+#             */
/*   Updated: 2024/12/30 12:21:33 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <signal.h>
# include <sys/types.h>
# include "libft.h"

void	send_pid(int *serv_pid, int *clnt_pid);
void	send_str(int *serv_pid, char *str, int *len);
void	send_size(int *serv_pid, int *len);

#endif
