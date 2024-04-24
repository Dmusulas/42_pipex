/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:40:51 by dmusulas          #+#    #+#             */
/*   Updated: 2024/04/24 21:24:17 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// In this scenario, ft_parse_cmds will create an array like this:
// ["/bin/cat", "/usr/bin/head", "/usr/bin/wc"], and the ft_parse_args will use ft_split to yield a 2D array like this one:
// [["cat"], ["head", "-n", "5"], ["wc", "-l"]] (remember to NULL terminate your arrays!).

// char **parse_args(*argv){}
// char **parse_args(*argv){}
#include "libft.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
	{
		envp++;
	}
	return (*envp);
}
