/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:04:40 by dmusulas          #+#    #+#             */
/*   Updated: 2024/05/11 18:12:58 by dmusulas         ###   ########.fr       */
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
# define ERR_ACCESS "Access"

typedef enum e_bool
{
	false,
	true
}	t_bool;

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
t_pipex	*init_pipex(int argc);
void	set_outfile(char *argv, t_pipex *pipex);
void	set_infile(char *argv, t_pipex *pipex);
char	**parse_cmds(int argc, char **argv, char **envp);
char	***parse_args(int argc, char **argv);
void	ft_exec(t_pipex *pipex, char **envp);

#endif
