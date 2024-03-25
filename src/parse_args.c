/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmusulas <dmusulas@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:40:51 by dmusulas          #+#    #+#             */
/*   Updated: 2024/03/25 19:43:01 by dmusulas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// In this scenario, ft_parse_cmds will create an array like this:
// ["/bin/cat", "/usr/bin/head", "/usr/bin/wc"], and the ft_parse_args will use ft_split to yield a 2D array like this one:
// [["cat"], ["head", "-n", "5"], ["wc", "-l"]] (remember to NULL terminate your arrays!).
// I recommend using a struct and storing all the data within it (see the struct I used below).
