/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 00:36:44 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/28 03:38:11 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_exitstatus(t_expand *exp, t_data *nv)
{
	if (!ft_strcmp(exp->ret1, "?"))
	{
		free(exp->ret1);
		free(exp->str);
		exp->str = ft_itoa(nv->exit_status);
		return (1);
	}
	return (0);
}

char	*help_expand(char **env, char *tmp)
{
	int		i;
	char	*value;
	int		size;

	i = 0;
	value = NULL;
	size = ft_strlen(tmp);
	while (env[i])
	{
		if (ft_strncmp(env[i], tmp, ft_size_nam(env[i], '=')))
			i++;
		else
			break ;
	}
	if (env[i] && (size == ft_size_nam(env[i], '=')))
		value = ft_substr(env[i], \
				(ft_size_nam(env[i], '=') + 1), ft_strlen(env[i]));
	return (value);
}

char	*help_ret_expand_val(char *str)
{
	int		i;
	int		j;
	char	*var;
	char	*tmp;

	j = find_equal_or_plus(str, '=');
	i = find_equal_or_plus(str, '+');
	var = NULL;
	if (j && j != -1)
	{
		tmp = ft_substr(str, 0, j);
		var = ft_substr(str, j, ft_strlen(str));
		str = tmp;
		free(tmp);
	}
	else if (i && i != -1)
	{
		tmp = ft_substr(str, 0, i);
		var = ft_strdup("+");
		str = tmp;
		free(tmp);
	}
	return (var);
}

void	get_value_exp(char **value, char *var, char *str, char **env)
{
	*value = help_expand(env, str);
	if (var)
	{
		str = *value;
		free ((*value));
		*value = ft_strjoin(str, var);
		free (var);
	}
}

char	*ret_expand_val(char *str, char **env)
{
	char	*value;
	char	*var;
	int		i;
	int		j;
	char	*tmp;

	j = find_equal_or_plus(str, '=');
	i = find_equal_or_plus(str, '+');
	var = NULL;
	if (j && j != -1)
	{
		tmp = ft_substr(str, 0, j);
		var = ft_substr(str, j, ft_strlen(str));
		str = tmp;
		free(tmp);
	}
	else if (i && i != -1)
	{
		tmp = ft_substr(str, 0, i);
		var = ft_strdup("+");
		str = tmp;
		free(tmp);
	}
	get_value_exp(&value, var, str, env);
	return (value);
}
