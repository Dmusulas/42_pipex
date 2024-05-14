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
#include <stdlib.h>

static void	read_from_urandom(int fd[2])
{
	char	buffer[1024];
	int		urandom_fd;
	ssize_t	bytes_read;

	urandom_fd = open("/dev/urandom", O_RDONLY);
	if (urandom_fd < 0)
		msg_error("Failed to open /dev/urandom");
	bytes_read = read(urandom_fd, buffer, sizeof(buffer));
	if (bytes_read > 0)
		write(fd[1], buffer, bytes_read);
	close(urandom_fd);
	exit(EXIT_SUCCESS);
}

static void	reader_process(int *fd, char *limiter, t_bool dev_urandom)
{
	char	*line;

	close(fd[0]);
	if (dev_urandom)
		read_from_urandom(fd);
	while (1)
	{
		line = get_next_line(0);
		if (!line || !ft_strncmp(line, limiter, ft_strlen(line) - 1))
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
}

static void	here_doc(char *limiter, t_pipex *pipex, t_bool dev_urandom)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		msg_error("Failed to create pipe");
	pid = fork();
	if (pid == -1)
		msg_error("Fork failed");
	if (pid == 0)
		reader_process(fd, limiter, dev_urandom);
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
		here_doc(argv[2], pipex, false);
		pipex->here_doc = true;
		pipex->cmd_count -= 1;
		pipex->cmd_start_position += 1;
	}
	else if (!ft_strncmp("/dev/urandom", argv[1], 13))
		here_doc("\n", pipex, true);
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
		pipex->out_fd = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		pipex->out_fd = open(argv, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->out_fd < 0)
		msg_error(ERR_OUTFILE);
}
