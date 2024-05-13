/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:40:51 by dmusulas          #+#    #+#             */
/*   Updated: 2024/05/07 21:14:12 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "pipex.h"
#include <unistd.h>

/**
 * This function finds a path of provided command from ENV PATH variable
 *
 * @param envp enviroment string
 * @return pointer to the PATH variable
 */
char	*find_path(char **envp)
{
	char	*prefix;
	int		prefix_len;

	prefix = "PATH=";
	prefix_len = ft_strlen(prefix);
	while (*envp)
	{
		if (ft_strncmp(prefix, *envp, prefix_len) == 0)
		{
			return (ft_substr(*envp, prefix_len, ft_strlen(*envp)
					- prefix_len));
		}
		envp++;
	}
	return (NULL);
}

/**
 * Utility function to free memory allocated by splitting PATHs.
 *
 * @param paths split paths resulting from ft_split function
 */
static void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

/**
 * Finds an executable cmd from path
 *
 * @param paths takes paths retrieved from env variable
 * @param cmd which cmd to find
 * @return a path to cmd in a system
 */
static char	*find_cmd(char *paths, char *cmd)
{
	char	*full_cmd;
	char	**paths_split;
	int		i;

	paths_split = ft_split(paths, ':');
	if (!paths_split)
		msg_error(ERR_MALLOC);
	i = 0;
	while (paths_split[i])
	{
		full_cmd = ft_strjoin(ft_strjoin(paths_split[i], "/"), cmd);
		if (!full_cmd)
		{
			free_paths(paths_split);
			return (NULL);
		}
		if (!access(full_cmd, X_OK))
			break ;
		free(full_cmd);
		i++;
	}
	free_paths(paths_split);
	return (full_cmd);
}

/**
 * This functions parses the argv to get correct path to executables
 *
 * @param argc argument count from main
 * @param argv argument array from main
 * @param envp environment variable array from the main
 * @return an array with paths to all executbales
 */
char	**parse_cmds(t_pipex *pipex, char **argv, char **envp)
{
	char	**cmds;
	char	*cmd;
	char	*paths;
	int		i;
	char	**temp;

	i = 0;
	paths = find_path(envp);
	cmds = malloc((pipex->cmd_count + 1) * sizeof(char *));
	if (!cmds)
		msg_error(ERR_MALLOC);
	while (i < pipex->cmd_count)
	{
		temp = ft_split(argv[i + pipex->cmd_start_position], ' ');
		cmd = find_cmd(paths, temp[0]);
		if (cmd)
			cmds[i] = cmd;
		free_paths(temp);
		i++;
	}
	cmds[i] = NULL;
	free(paths);
	return (cmds);
}

/**
 * This functions parses the argv to get commands and their arguments
 *
 * @param argc argument count from main
 * @param argv argument array from main
 * @return a 2D array with commands and their args
 */
char	***parse_args(t_pipex *pipex, char **argv)
{
	char	***args;
	int		i;

	i = 0;
	args = malloc((pipex->cmd_count + 1) * sizeof(char **));
	if (!args)
		msg_error(ERR_MALLOC);
	while (i < pipex->cmd_count)
	{
		args[i] = ft_split(argv[i + pipex->cmd_start_position], ' ');
		i++;
	}
	args[i] = NULL;
	return (args);
}
