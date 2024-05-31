/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:31:08 by dmusulas          #+#    #+#             */
/*   Updated: 2024/04/24 21:20:25 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Displays an error message and terminates the program with a failure status.
 *
 * @param err The error message to be displayed.
 */
void	msg_error(char *err, t_pipex *pipex)
{
	perror(err);
	if (pipex)
		free_pipex(pipex);
	exit(errno);
}
