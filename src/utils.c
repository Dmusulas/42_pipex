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
	pipex->cmd_count = argc - 3;
	pipex->cmd_start_position = 2;
	pipex->here_doc = false;
	pipex->is_invalid_infile = false;
	return (pipex);
}

/**
 */
void	free_pipex(t_pipex *pipex)
{
	int	i;
	int	j;

	free_2darray(pipex->cmd_paths);
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
	free(pipex);
}

/**
 * Utility function to free memory allocated by splitting PATHs.
 *
 * @param paths split paths resulting from ft_split function
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
