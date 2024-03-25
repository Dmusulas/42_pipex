/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 19:43:52 by dmusulas          #+#    #+#             */
/*   Updated: 2024/03/25 19:21:25 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft.h"

int	main(int argc, char *argv[])
{
	if (argc > 4)
	{
		ft_printf("works, %s", argv[1]);
	}
	else
	{
		return (EXIT_SUCCESS);
	}
	return (EXIT_SUCCESS);
}
