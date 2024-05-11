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
 * Finds an executable cmd from path
 *
 * @param paths takes paths retrieved from env variable
 * @param cmd which cmd to find
 * @return a path to cmd in a system
 */
static char	*find_cmd(char *paths, char *cmd)
{
	char	*temp;
	char	*full_cmd;
	char	**paths_split;

	paths_split = ft_split(paths, ':');
	if (!paths_split)
		return (NULL);
	while (*paths_split)
	{
		temp = ft_strjoin(*paths_split, "/");
		if (!temp)
			return (NULL);
		full_cmd = ft_strjoin(temp, cmd);
		if (!full_cmd)
			return (NULL);
		if (!access(full_cmd, X_OK))
		{
			break ;
		}
		paths_split++;
	}
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
char	**parse_cmds(int cmd_count, char **argv, char **envp)
{
	char	**cmds;
	char	*cmd;
	char	*paths;
	int		i;

	i = 2;
	paths = find_path(envp);
	cmds = malloc((cmd_count) * sizeof(char *));
	while (i <= cmd_count)
	{
		cmd = find_cmd(paths, ft_split(argv[i], ' ')[0]);
		if (cmd)
		{
			cmds[i - 2] = cmd;
		}
		i++;
	}
	cmds[i - 2] = NULL;
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
char	***parse_args(int cmd_count, char **argv)
{
	char	***args;
	int		i;

	i = 0;
	args = malloc((cmd_count) * sizeof(char **));
	while (i < cmd_count - 1)
	{
		args[i] = ft_split(argv[i + 2], ' ');
		i++;
	}
	args[cmd_count] = NULL;
	return (args);
}
