/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:40:56 by dmusulas          #+#    #+#             */
/*   Updated: 2024/04/24 21:19:31 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: Psuedo-code to execute the 
void	ft_exec()
{
	pipe()
	fork()
	if (child)
	{
		dup2()
		execve()
	}
	else
	{
		close()
	}
}
	// int	fds[2];
	// int	in_fd;
	// int	out_fd;
	//
	// in_fd = open(argv[1], O_RDONLY);
	// out_fd = open(argv[argc - 1], O_WRONLY | O_CREAT, 0644);
	// for (int i = 2; i < argc - 1; i++)
	// {
	// 	pipe(fds);
	// 	if (fork() == 0)
	// 	{
	// 		dup2(in_fd, 0);
	// 		close(fds[0]);
	// 		if (i != argc - 2)
	// 		{
	// 			dup2(fds[1], 1);
	// 		}
	// 		else
	// 		{
	// 			dup2(out_fd, 1);
	// 		}
	// 		close(fds[1]);
	// 		execve(argv[i], &argv[i], envp);
	// 		exit(1);
	// 	}
	// 	close(in_fd);
	// 	in_fd = fds[0];
	// 	close(fds[1]);
	// }
	// close(out_fd);
	// while (
	// 	wait(NULL) > 0);
	// return (0);
