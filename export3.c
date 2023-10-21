/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 20:49:20 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/28 01:19:34 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_new_var_in_env(char *str, t_export *tmpe, char c, t_data *nv)
{
	char	*tmp;

	if (c == '=')
		lstadd_back_environement(&nv->environement, \
		creation_node_in_env(ft_strdup(str), \
		tmpe->var, ft_substr(str, tmpe->i + 1, ft_strlen(str) - tmpe->i)));
	else if (c == '+')
	{
		str = str_sans_plus(str);
		tmp = ft_substr(str, tmpe->i + 1, ft_strlen(str) - tmpe->i);
		if (ft_strlen(tmp) == 1)
		{
			free(tmp);
			tmp = ft_strdup("");
		}
		lstadd_back_environement(&nv->environement, creation_node_in_env(str,
				tmpe->var, tmp));
	}
	else
	{
		lstadd_back_environement(&nv->environement, \
				creation_node_in_env(ft_strdup(tmpe->var), \
				ft_strdup(tmpe->var), NULL));
		free(tmpe->var);
	}
}

int	help_export(int flag, char *var, char *varr)
{
	if (!flag || (!(*var == '+' && *(var + 1) == '=') \
		&& *var != '=' && *var))
	{
		error_args_export(varr);
		return (1);
	}
	return (0);
}
