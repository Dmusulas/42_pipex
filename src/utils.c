/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 20:54:06 by dmusulas          #+#    #+#             */
/*   Updated: 2024/05/07 21:26:00 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Initiates pipex struct. Argc - 3 is simply:
 * argument count - program_name (i = 0) - infile (i = 1) - outfile (i = argc)
 *
 * @param argc is the argument count
 * @return a pointer to newly created struct
 */
t_pipex	*init_pipex(int argc)
{
	t_pipex	*pipex;

	pipex = malloc(1 * sizeof(t_pipex));
	if (!pipex)
		msg_error(ERR_MALLOC);
	pipex->cmd_count = argc - 3;
	pipex->cmd_start_position = 2;
	pipex->here_doc = false;
	pipex->is_invalid_infile = false;
	pipex->cmd_paths = NULL;
	pipex->cmd_args = NULL;
	pipex->in_fd = -1;
	pipex->out_fd = -1;
	return (pipex);
}

/**
 */
void	free_pipex(t_pipex *pipex)
{
	int	i;
	int	j;

	if (pipex->cmd_paths)
		free_2darray(pipex->cmd_paths);
	if (pipex->cmd_args)
	{
		i = 0;
		while (pipex->cmd_args[i])
		{
			j = 0;
			while (pipex->cmd_args[i][j])
			{
				free(pipex->cmd_args[i][j]);
				j++;
			}
			free(pipex->cmd_args[i]);
			i++;
		}
		free(pipex->cmd_args);
	}
	close(pipex->in_fd);
	close(pipex->out_fd);
	free(pipex);
}

/**
 * Utility function to free memory allocated by splitting PATHs.
 *
 * @param array the 2d array to be freed
 */
void	free_2darray(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
