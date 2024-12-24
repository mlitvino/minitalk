/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:26:51 by mlitvino          #+#    #+#             */
/*   Updated: 2024/12/24 14:28:01 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include "libft.h"
# include <signal.h>
# include <sys/types.h>

void	send_pid(int *serv_pid, int *clnt_pid);
void	send_str(int *serv_pid, char *str, int *len);
void	send_size(int *serv_pid, int *len);


#include <stdio.h>
#include <string.h>

#endif
