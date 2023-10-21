/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:32:47 by nait-ali          #+#    #+#             */
/*   Updated: 2023/10/04 20:41:33 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	find_pwd_in_env(t_environement *tmp, t_cmd *cmd)
{
	while (tmp)
	{
		if (!ft_strcmp(tmp->cle, "PWD"))
		{
			ft_putstr_fd(tmp->valeur, cmd->fileout);
			ft_putstr_fd("\n", cmd->fileout);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	ft_pwd(t_cmd *cmd, t_data *nv)
{
	t_environement	*tmp;

	tmp = nv->environement;
	find_pwd_in_env(tmp, cmd);
	nv->exit_status = 0;
}
