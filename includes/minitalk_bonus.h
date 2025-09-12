/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 00:28:55 by marvin            #+#    #+#             */
/*   Updated: 2025/09/10 00:28:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

#define BUFFER_SIZE 1024
#define CHUNK_SIZE 1024

void	error_exit(char *msg);
void free_split(char **arr);

typedef struct s_state
{
	int     bit;
	int     c;
	pid_t   client_pid;
}   t_state;


#endif