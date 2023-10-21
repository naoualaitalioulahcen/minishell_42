/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 23:40:46 by araiteb           #+#    #+#             */
/*   Updated: 2023/10/04 18:25:08 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_sizexp(char *line, int *i, t_expand *exp)
{
	exp->size = 0;
	while (line[*i] && line[*i] != '$')
	{
		exp->size++;
		(*i)++;
	}
}

void	check_valu_exp(t_expand *exp, char **env)
{
	char	*tmp;

	tmp = NULL;
	exp->value = NULL;
	if (exp->ret1 && !check_doll(exp->ret1, '$'))
	{
		exp->value = ret_expand_val(exp->ret1, env);
		tmp = exp->str;
		exp->str = ft_strjoin(exp->ret, exp->value);
		ft_free_str(exp->value);
		exp->value = exp->str;
		exp->str = ft_strjoin(tmp, exp->value);
		ft_free_str (exp->value);
		ft_free_str(tmp);
	}
}

void	help_option_expand(char *line, char **env, t_expand *exp, t_data *nv)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		exp->ret = NULL;
		exp->ret1 = NULL;
		exp->start = i;
		get_sizexp(line, &i, exp);
		i++;
		if (exp->size > 0)
			exp->ret = ft_substr(line, exp->start, exp->size);
		exp->start = i;
		get_sizexp(line, &i, exp);
		exp->ret1 = ft_substr(line, exp->start, exp->size);
		if (check_if_exitstatus(exp, nv))
			break ;
		check_valu_exp(exp, env);
		(ft_free_str(exp->ret), ft_free_str(exp->ret1));
	}
}

char	*option_expand(char *line, char **env, t_data *nv)
{
	t_expand	*exp;
	char		*tmp;

	exp = (t_expand *)malloc(sizeof(t_expand));
	if (!exp)
		return (NULL);
	tmp = NULL;
	exp->str = NULL;
	help_option_expand(line, env, exp, nv);
	tmp = ft_strtrim(exp->str, " ");
	ft_free_str (exp->str);
	return (free(exp), tmp);
}

void	expand_env_variable(char **option, char **env, t_data *nv)
{
	char	*str;
	int		i;
	char	*new;

	i = 0;
	str = NULL;
	while (option && option[i])
	{
		str = ft_strdup(option[i]);
		ft_free_str (option[i]);
		if (str[0] != '"' && check_doll(str, '$') == 1 && ft_strlen(str) > 1
			&& ((nv->dqflg == 2 || (!nv->dqflg && !nv->sqflg)
					|| (nv->dqflg != 3 && !nv->sqflg))))
		{
			new = subc_quots(str);
			option[i] = option_expand(new, env, nv);
			ft_free_str(new);
		}
		else
			option[i] = subc_quots(str);
		ft_free_str(str);
		i++;
	}
}
