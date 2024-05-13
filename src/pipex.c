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

#include "libft.h"
#include "pipex.h"

void	child_process(t_pipex *pipex, int i, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		msg_error("Pipe");
	pid = fork();
	if (pid == -1)
		msg_error("Error");
	if (pid == 0)
	{
		close(fd[0]);
		if (i == pipex->cmd_count - 1)
			dup2(pipex->out_fd, STDOUT_FILENO);
		else
			dup2(fd[1], STDOUT_FILENO);
		execve(pipex->cmd_paths[i], pipex->cmd_args[i], envp);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	ft_exec(t_pipex *pipex, char **envp)
{
	int	i;

	i = 0;
	dup2(pipex->in_fd, STDIN_FILENO);
	while (i < pipex->cmd_count)
	{
		child_process(pipex, i, envp);
		i++;
	}
}
