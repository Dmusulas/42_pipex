/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:40:51 by dmusulas          #+#    #+#             */
/*   Updated: 2024/04/24 21:51:04 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
	{
		envp++;
	}
	return (*envp);
}

static char	*find_cmd(char *paths, char *cmd)
{
	char	*temp;
	char	*return_cmd;

	while (*paths)
	{
		temp = ft_strjoin(paths, "/");
		return_cmd = ft_strjoin(temp, cmd);
		free(temp);
		if (!access(return_cmd, X_OK))
			return (return_cmd);
		free(return_cmd);
		paths++;
	}
	return (NULL);
}

char	*parse_cmds(int argc, char **argv, char **envp)
{
	char	**cmds;
}

// char	**parse_args(char **argv)
// {
//
// }
