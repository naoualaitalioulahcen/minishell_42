/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 04:06:07 by nait-ali          #+#    #+#             */
/*   Updated: 2023/10/02 09:01:21 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	help_get_rd3(t_substruct **cmd, t_tmp *var, t_data *nv)
{
	int	is_tr;

	is_tr = 0;
	if ((*cmd)->type == heredoc || \
	((*cmd)->type == rd_input))
	{
		if (!help_get_rd2(var, cmd, nv))
			return (0);
		is_tr = 1;
	}
	else if (!is_tr && var->ls && var->ls->prev)
		var->ls->filein = var->fds[var->ls->i - 1][0];
	return (1);
}

int	get_rd(t_substruct **cmd, t_tmp *var, t_data *nv)
{
	int		is_tr;

	is_tr = 0;
	if (!help_get_rd3(cmd, var, nv))
		return (0);
	is_tr = 0;
	if (((*cmd) && (*cmd)->type == rd_output)
		|| ((*cmd) && (*cmd)->type == rd_output_append))
	{
		help_get_rd(cmd, var, nv);
		if (var->ls->fileout == -1)
			return (0);
		is_tr = 1;
		(*cmd) = (*cmd)->next;
	}
	if (!is_tr && var->ls && var->ls->next)
		var->ls->fileout = var->fds[var->ls->i][1];
	return (1);
}
