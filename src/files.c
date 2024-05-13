/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:35:05 by dmusulas          #+#    #+#             */
/*   Updated: 2024/05/07 19:41:21 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

void	here_doc(char *limiter, t_pipex *pipex)
{
	char	*line;
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		msg_error("Failed to create pipe");
	pid = fork();
	if (pid == -1)
		msg_error("Fork failed");
	if (pid == 0)
	{
		close(fd[0]);
		while (1)
		{
			line = get_next_line(0);
			if (!line || !ft_strncmp(line, limiter, ft_strlen(line) - 1))
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(fd[1]);
		pipex->in_fd = fd[0];
		wait(NULL);
	}
}

void	set_infile(char **argv, t_pipex *pipex)
{
	if (!ft_strncmp("here_doc", argv[1], 9))
	{
		here_doc(argv[2], pipex);
		pipex->here_doc = true;
		pipex->cmd_count = pipex->cmd_count - 1;
		pipex->cmd_start_position = pipex->cmd_start_position + 1;
	}
	else
	{
		if (!access(argv[1], R_OK))
		{
			pipex->in_fd = open(argv[1], O_RDONLY);
			if (pipex->in_fd < 0)
				msg_error(ERR_INFILE);
		}
		else
			msg_error(ERR_ACCESS);
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
