/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnogueir <jnogueir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 11:52:58 by jnogueir          #+#    #+#             */
/*   Updated: 2025/09/12 12:00:02 by jnogueir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "libft.h"

static void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	main(int argc, char **argv)
{
	int		server_pid;
	char	*with_sep;
	char	**chunks;
	int		i;

	if (argc != 3)
		return (error_exit("Uso: ./client <PID><menssagem>\n"), 1);
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
	{
		error_exit("PID inválido\n");
		return (1);
	}
	with_sep = insert_separators(argv[2]);
	chunks = ft_split(with_sep, '|');
	i = 0;
	while (chunks[i])
		send_string(server_pid, chunks[i++]);
	send_char(server_pid, '\0');
	free(with_sep);
	free_split(chunks);
}
