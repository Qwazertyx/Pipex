/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsedat <vsedat@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 10:18:19 by vsedat            #+#    #+#             */
/*   Updated: 2022/02/04 10:27:50 by vsedat           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

void	pipex(int f1, int f2)
{
	int		end[2];
	int		id;

	pipe(end);
	id = fork();
	if (id < 0)
		return (0 * write (1, "Fork Error\n", 11));
	if (!id)
		child_process(f1, cmd1);
	else
		parent_process(f2, cmd2);
}
