/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:40:56 by dmusulas          #+#    #+#             */
/*   Updated: 2024/04/24 21:34:38 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Redirects the old file descriptor to the new file descriptor
 * and closes the old one.
 *
 * @param old_fd The file descriptor to be redirected.
 * @param new_fd The file descriptor to redirect to.
 */
static void	redirect_fds(int old_fd, int new_fd)
{
	dup2(old_fd, new_fd);
	close(old_fd);
}

/**
 * Sets up the pipes and redirects file descriptors for a specific
 * command in the pipeline.
 *

	* @param pipex A pointer to a t_pipex structure containing pipeline information.
 * @param fd An array of two integers representing the pipe file descriptors.
 * @param i The index of the current command in the pipeline.
 */
static void	setup_pipes(t_pipex *pipex, int *fd, int i)
{
	if (i == 0)
		redirect_fds(pipex->in_fd, STDIN_FILENO);
	if (i == pipex->cmd_count - 1)
		redirect_fds(pipex->out_fd, STDOUT_FILENO);
	if (i < pipex->cmd_count - 1)
	{
		close(fd[0]);
		redirect_fds(fd[1], STDOUT_FILENO);
	}
}

/**
 * Executes a command using execve, replacing the current process
 * image with a new process image.
 *

	* @param pipex A pointer to a t_pipex structure containing pipeline information.
 * @param envp An array of environment variables.
 * @param i The index of the command to execute in the pipeline.
 */
static void	execute_cmd(t_pipex *pipex, char **envp, int i)
{
	if (!access(pipex->cmd_paths[i], X_OK))
		execve(pipex->cmd_paths[i], pipex->cmd_args[i], envp);
	free_pipex(pipex);
	exit(EXIT_FAILURE);
}

/**
 * Handles the creation and setup of a child process for executing
 * a command in the pipeline.
 *

	* @param pipex A pointer to a t_pipex structure containing pipeline information.
 * @param envp An array of environment variables.
 * @param i The index of the current command in the pipeline.
 */
static void	child_process(t_pipex *pipex, char **envp, int i)
{
	int		fd[2];
	pid_t	pid;

	if (i < pipex->cmd_count - 1 && pipe(fd) == -1)
		msg_error(ERR_PIPE, pipex);
	pid = fork();
	if (pid == -1)
		msg_error(ERR_FORK, pipex);
	else if (pid == 0)
	{
		setup_pipes(pipex, fd, i);
		execute_cmd(pipex, envp, i);
	}
	else
	{
		if (i < pipex->cmd_count - 1)
		{
			close(fd[1]);
			redirect_fds(fd[0], STDIN_FILENO);
		}
	}
}

/**
 * Executes all commands in the pipeline by creating child processes
 * for each command.
 *

	* @param pipex A pointer to a t_pipex structure containing pipeline information.
 * @param envp An array of environment variables.
 */
void	ft_exec(t_pipex *pipex, char **envp)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count)
	{
		child_process(pipex, envp, i);
		i++;
	}
	while (wait(NULL) > 0)
		;
}
