/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 20:54:06 by dmusulas          #+#    #+#             */
/*   Updated: 2024/05/07 21:26:00 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*init_pipex(int argc)
{
	t_pipex	*pipex;

	pipex = malloc(1 * sizeof(t_pipex));
	pipex->cmd_count = argc - 2;
	return (pipex);
}
