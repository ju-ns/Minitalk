/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnogueir <jnogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:37:44 by jnogueir          #+#    #+#             */
/*   Updated: 2025/09/05 13:37:51 by jnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
#define SIZE 50
#define BUFFER_SIZE 1024


void	send_char(int pid, char c);
void	error_exit(char *msg);
void send_string(int pid, const char *str);
char *insert_separators(const char *str);


#endif