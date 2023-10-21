/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outi_exect.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 02:54:53 by araiteb           #+#    #+#             */
/*   Updated: 2023/10/02 09:02:37 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_doll(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_size_nam(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c)
		i++;
	return (i);
}

void	get_option(char ***option, t_substruct *tmps)
{
	while (tmps)
	{
		if ((tmps->type != word) && (tmps->type != pip))
			tmps = tmps->next->next;
		if (tmps && (tmps->type == word || tmps->type == pip))
		{
			(*option) = __resize((*option), tmps->data);
			tmps = tmps->next;
		}
	}
}

int	checkrd(t_cmd *tmp, t_substruct *tmps, int **fds, t_data *nv)
{
	t_tmp	var;

	var.ls = tmp;
	var.fds = fds;
	while (tmps)
	{
		if (tmps->next && tmps->next->type != word)
			tmps = tmps->next;
		if ((tmps && !tmps->prev) || tmps->type != word)
		{
			if (!get_rd(&tmps, &var, nv))
				return (0);
		}
		tmps = tmps->next;
	}
	return (1);
}

void	wait_pd(t_varn *var, int size, t_data *nv)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < size)
	{
		if ((var->pd[i]) != -1)
			waitpid((var->pd[i]), &status, 0);
		i++;
	}
	signals_in_child_process(status, nv);
}
