/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:35:05 by dmusulas          #+#    #+#             */
/*   Updated: 2024/04/24 21:20:06 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

void	set_infile(char **argv, t_pipex *pipex)
{
	if (ft_strncmp("here_doc", argv[1], 9))
	{
		//TODO: added here_doc implementations
		//here_doc(argv[2], pipex)
	}
	else
	{
		if (!access(argv[1], R_OK))
		{
			pipex->in_fd = open(argv[1], O_RDONLY);
			if (pipex->in_fd < 0)
				msg_error(ERR_INFILE);
		}
	}
}

void	set_outfile(char *argv, t_pipex *pipex)
{
	if (pipex->here_doc)
		pipex->out_fd = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0000644);
	else
		pipex->out_fd = open(argv, O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (pipex->out_fd < 0)
		msg_error(ERR_OUTFILE);
}
