/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:04:40 by dmusulas          #+#    #+#             */
/*   Updated: 2024/04/24 21:21:00 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# define ERR_INFILE "Infile"
# define ERR_OUTFILE "Outfile"

typedef enum e_bool { false, true }	t_bool;

typedef struct s_pipex
{
	int		in_fd;
	int		out_fd;
	t_bool	here_doc;
	t_bool	is_invalid_infile;
	char	**cmd_paths;
	char	***cmd_args;
	int		cmd_count;
}	t_pipex;

void	msg_error(char *err);
t_pipex	*init_pipex(void);
void	set_outfile(char *argv, t_pipex *pipex);
void	set_infile(char **argv, t_pipex *pipex);

#endif
