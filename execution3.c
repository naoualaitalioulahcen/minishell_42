/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 00:55:54 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/28 00:48:12 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close(t_cmd *ls)
{
	if (ls->filein != 0)
		close (ls->filein);
	if (ls->fileout != 1)
		close (ls->fileout);
}

void	ft_free_matrix(int **str, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		close(str[i][0]);
		close(str[i][1]);
		free (str[i]);
		i++;
	}
	free (str);
}

void	ft_creat_pipe(int size, int **fds, t_data *nv)
{
	int	i;

	i = 0;
	while (i < size)
	{
		fds[i] = malloc(sizeof(int) * 2);
		if (!fds)
			return ;
		if (pipe(fds[i]) == -1)
		{
			(ft_free_matrix(fds, i), write(2, "error piping\n", 14));
			nv->exit_status = 1;
			break ;
		}
		i++;
	}
}

void	free_execution(t_varn *var, t_cmd *list)
{
	if (var->fds)
		ft_free_matrix(var->fds, ft_lstsize(list));
	(free (var->pd), free(var));
}
