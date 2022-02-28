/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsedat <vsedat@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 14:23:30 by vsedat            #+#    #+#             */
/*   Updated: 2022/02/28 12:30:57 by vsedat           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/pipex.h"

void	terminate(void)
{
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}

void	errorcmd(char **cmd)
{
	write(2, "Error: command not found\n", 25);
	free_split(cmd);
	exit(EXIT_FAILURE);
}

void	free_split(char **args)
{
	int	size;
	int	i;

	i = 0;
	size = 0;
	while (args[size])
		size++;
	while (i < size)
		free(args[i++]);
	free(args);
}
