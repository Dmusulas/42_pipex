/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 19:43:52 by dmusulas          #+#    #+#             */
/*   Updated: 2024/04/24 21:42:42 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*pipex;

	pipex = init_pipex();
	set_infile(argv, pipex);
	set_outfile(argv[argc - 1], pipex);
}
