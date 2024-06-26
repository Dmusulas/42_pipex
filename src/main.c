/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 19:43:52 by dmusulas          #+#    #+#             */
/*   Updated: 2024/05/14 21:00:11 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

int	main(int argc, char *argv[], char **envp)
{
	t_pipex	*pipex;

	if (argc >= 5)
	{
		pipex = init_pipex(argc);
		set_infile(argv, pipex);
		set_outfile(argv[argc - 1], pipex);
		pipex->cmd_paths = parse_cmds(pipex, argv, envp);
		pipex->cmd_args = parse_args(pipex, argv);
		ft_exec(pipex, envp);
		close(pipex->in_fd);
		close(pipex->out_fd);
		free_pipex(pipex);
	}
	else
	{
		ft_printf("Program usage: ./pipex <infile|here_doc LIMITER> \
{cmd...N} <outfile>\n");
		exit(EXIT_FAILURE);
	}
}
