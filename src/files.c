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

/**
 * Reads random data from /dev/urandom and writes it to a pipe.
 *
 * @param fd An array of two integers representing the pipe file descriptors.
 */
void	read_from_urandom(int fd[2], t_pipex *pipex)
{
	char	buffer[1024];
	int		urandom_fd;
	ssize_t	bytes_read;

	urandom_fd = open("/dev/urandom", O_RDONLY);
	if (urandom_fd < 0)
		msg_error("Failed to open /dev/urandom", pipex);
	bytes_read = read(urandom_fd, buffer, sizeof(buffer));
	close(urandom_fd);
	if (bytes_read > 0)
		write(fd[1], buffer, bytes_read);
	close(fd[1]);
}

/**
 * Handles the reading process for either /dev/urandom or user input,
	writing to a pipe.
 *
 * @param fd An array of two integers representing the pipe file descriptors.
 * @param limiter A string used to determine when to stop reading user input.
 * @param dev_urandom A boolean indicating whether to read from /dev/urandom.
 */
void	reader_process(int fd[2], char *limiter, t_bool dev_urandom,
		t_pipex *pipex)
{
	char	*line;

	close(fd[0]);
	if (dev_urandom)
		read_from_urandom(fd, pipex);
	else
	{
		while (1)
		{
			line = get_next_line(0);
			if (!line || !ft_strncmp(line, limiter, ft_strlen(line) - 1))
			{
				free(line);
				break ;
			}
			write(fd[1], line, ft_strlen(line));
			free(line);
		}
	}
	close(fd[1]);
	free_pipex(pipex);
	exit(EXIT_SUCCESS);
}

/**
 * Sets up a pipe and forks a process to handle reading input for
 * the here_doc functionality.
 *
 * @param limiter A string used to determine when to stop reading user input.
 * @param pipex A pointer to a t_pipex structure containing pipeline
 * information.
 * @param dev_urandom A boolean indicating whether to read from /dev/urandom.
 */
void	here_doc(char *limiter, t_pipex *pipex, t_bool dev_urandom)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		msg_error(ERR_PIPE, pipex);
	pid = fork();
	if (pid == -1)
		msg_error(ERR_FORK, pipex);
	if (pid == 0)
		reader_process(fd, limiter, dev_urandom, pipex);
	else
	{
		close(fd[1]);
		pipex->in_fd = fd[0];
		wait(NULL);
	}
}

/**
 * Sets the input file for the pipeline, handling here_doc
 *
 * @param argv An array of arguments passed to the program.
 * @param pipex A pointer to a t_pipex structure containing pipeline
 * information.
 */
void	set_infile(char **argv, t_pipex *pipex)
{
	if (!ft_strncmp("here_doc", argv[1], 9))
	{
		here_doc(argv[2], pipex, false);
		pipex->here_doc = true;
		pipex->cmd_count -= 1;
		pipex->cmd_start_position += 1;
	}
	else
	{
		if (access(argv[1], R_OK) == -1)
			msg_error(ERR_ACCESS, pipex);
		pipex->in_fd = open(argv[1], O_RDONLY);
		if (pipex->in_fd < 0)
			msg_error(ERR_INFILE, pipex);
	}
}

/**
 * Sets the output file for the pipeline,
	handling here_doc case for append mode.
 *
 * @param argv The output file path.
	* @param pipex A pointer to a t_pipex structure containing pipeline information.
 */
void	set_outfile(char *argv, t_pipex *pipex)
{
	if (pipex->here_doc)
		pipex->out_fd = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		pipex->out_fd = open(argv, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipex->out_fd < 0)
		msg_error(ERR_OUTFILE, pipex);
}
