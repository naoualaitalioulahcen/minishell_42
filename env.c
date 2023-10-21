/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:32:29 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/28 00:32:00 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(char *cle, char *valeur, t_cmd *cmd)
{
	ft_putstr_fd(cle, cmd->fileout);
	ft_putstr_fd("=", cmd->fileout);
	ft_putstr_fd(valeur, cmd->fileout);
	ft_putstr_fd("\n", cmd->fileout);
}

void	ft_env(t_cmd *cmd, t_data *nv)
{
	t_environement	*env;

	env = nv->environement;
	while (env)
	{
		if (env->valeur)
			print_env(env->cle, env->valeur, cmd);
		env = env->next;
	}
	nv->exit_status = 0;
}
