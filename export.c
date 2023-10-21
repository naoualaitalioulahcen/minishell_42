/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:32:37 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/03 18:32:37 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	add_val_var_env(t_environement *tmp, char *str, int i, char c)
{
	char	*val;
	char	*var;
	char	*ch;

	if (c == '+')
	{
		ch = str_sans_plus(str);
		val = ft_substr(ch, i + 1, ft_strlen(str) - i - 1);
		var = ft_strjoin(tmp->valeur, val);
		free(tmp->valeur);
		free(val);
		free(ch);
		tmp->valeur = var;
	}
	else
	{
		var = ft_substr(str, i + 1, ft_strlen(str) - i);
		free(tmp->valeur);
		tmp->valeur = var;
	}
	var = ft_strjoin(tmp->cle, "=");
	free(tmp->env);
	tmp->env = ft_strjoin(var, tmp->valeur);
	free(var);
}

static	int	search_key_in_env(char *str, t_export *tmpp, char c, t_data *nv)
{
	t_environement	*tmp;

	tmp = nv->environement;
	while (tmp)
	{
		if (!ft_strcmp(tmpp->var, tmp->cle))
		{
			if (c)
			{
				add_val_var_env(tmp, str, tmpp->i, c);
				free(tmpp->var);
			}
			else
				free(tmpp->var);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	export_variables(char *str, char c, t_data *nv)
{
	int			i;
	t_export	tmp;

	i = 0;
	if (c)
	{
		tmp.i = find_equal_or_plus(str, c);
		tmp.var = ft_substr(str, 0, tmp.i);
	}
	else
		tmp.var = ft_strdup(str);
	if (!search_key_in_env(str, &tmp, c, nv))
		export_new_var_in_env(str, &tmp, c, nv);
}

void	export(char *var, char **option, t_data *nv, int i)
{
	int		flag;
	int		bad;

	flag = 0;
	bad = 0;
	while (option[++i])
	{
		flag = 0;
		var = option[i];
		while (check_first_c(*var))
		{
			flag++;
			var++;
		}
		while (check_first_c2(*var))
			var++;
		if (help_export(flag, var, option[i]))
		{
			nv->exit_status = 1;
			bad = 1;
		}
		else
			export_variables(option[i], *var, nv);
	}
	!bad && (nv->exit_status = 0);
}

void	ft_export(t_cmd *cmd, char **option, t_data *nv)
{
	t_substruct	*varr;
	char		*var;
	int			i;

	var = NULL;
	i = 0;
	varr = cmd->s_substruct->next;
	if (!varr || varr->data[0] == '>' || varr->data[0] == '<')
		print_environement(cmd, nv);
	else
		export(var, option, nv, i);
}
