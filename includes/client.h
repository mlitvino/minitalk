/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:52:08 by mlitvino          #+#    #+#             */
/*   Updated: 2025/02/26 12:54:45 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H
# include <signal.h>
# include <sys/types.h>
# include "libft.h"

void	send_len(pid_t *serv_pid, int *len);
void	send_str(pid_t *serv_pid, char *str, int *len);

#endif
