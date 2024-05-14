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

static void	redirect_fds(int old_fd, int new_fd)
{
	dup2(old_fd, new_fd);
	close(old_fd);
}

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

static void	execute_cmd(t_pipex *pipex, char **envp, int i)
{
	execve(pipex->cmd_paths[i], pipex->cmd_args[i], envp);
	msg_error("Execution failed");
}

static void	child_process(t_pipex *pipex, char **envp, int i)
{
	int		fd[2];
	pid_t	pid;

	if (i < pipex->cmd_count - 1 && pipe(fd) == -1)
		msg_error("Pipe creation failed");
	pid = fork();
	if (pid == -1)
		msg_error("Fork failed");
	else if (pid == 0)
	{
		setup_pipes(pipex, fd, i);
		execute_cmd(pipex, envp, i);
	}
	if (i < pipex->cmd_count - 1)
	{
		close(fd[1]);
		redirect_fds(fd[0], STDIN_FILENO);
	}
}

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
