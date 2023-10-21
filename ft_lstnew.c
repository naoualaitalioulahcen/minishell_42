/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 01:04:56 by araiteb           #+#    #+#             */
/*   Updated: 2023/10/03 10:30:49 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_inside_quotes(char *cmd, int *i, int type)
{
	char	*str;
	int		size;
	int		start;

	start = *i;
	size = 0;
	while (cmd[*i])
	{
		if (cmd[*i] == type)
			break ;
		size++;
		(*i)++;
	}
	if (size == 0)
		return (NULL);
	str = ft_substr(cmd, start, size);
	return (str);
}

char	*get_outside_quotes(char *cmd, int *i)
{
	char	*rest;
	int		start;
	int		size;

	rest = NULL;
	size = 0;
	start = *i;
	while (cmd[*i] && is_alpha(cmd[*i]))
	{
		size++;
		(*i)++;
	}
	rest = ft_substr(cmd, start, size);
	return (rest);
}

void	init_list(t_cmd **l, char *cmd)
{
	(*l)->data = ft_strdup(cmd);
	(*l)->fileout = 1;
	(*l)->filein = 0;
	(*l)->next = NULL;
	(*l)->prev = NULL;
	(*l)->i = 0;
}

char	*separt_cond(char *cmd, int *i, t_data *nv, t_cmd *l)
{
	char	*str;

	nv->sqflg = 0;
	nv->dqflg = 0;
	if (cmd[*i] == '\'' || cmd[*i] == '"')
		str = get_str1(cmd, i, l, nv);
	else if (cmd[*i] == '>' || cmd[*i] == '<')
		str = get_str2(cmd, i, nv, l);
	else
		str = get_command(cmd, i, l, nv);
	return (str);
}

t_cmd	*ft_lstnew(char *cmd, t_data *nv)
{
	t_cmd		*l;
	t_substruct	*new;
	char		*str;
	int			i;

	str = NULL;
	l = malloc(sizeof(t_cmd));
	if (!l)
		return (NULL);
	l->s_substruct = NULL;
	i = 0;
	while (cmd[i])
	{
		str = separt_cond(cmd, &i, nv, l);
		if (str)
		{
			new = n_lstnew(str);
			n_lstadd_back(&(l->s_substruct), new);
		}
		while (cmd[i] == ' ' || cmd[i] == '\t')
			i++;
		ft_free_str(str);
	}
	init_list(&l, cmd);
	return (l);
}
