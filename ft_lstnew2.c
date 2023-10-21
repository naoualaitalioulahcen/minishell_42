/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 03:14:54 by araiteb           #+#    #+#             */
/*   Updated: 2023/10/04 07:21:04 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	line_filpip(char *line)
{
	char	*str;

	if (!check_linesps(line))
		return (free(line), 0);
	if (non_closed_quotes(line))
		return (0);
	if (line[ft_strlen(line) - 1] == '|'
		&& ft_strlen(line) > 1 && line[0] != '>' && line[0] != '|')
	{
		str = line;
		line = ft_strjoin(str, " newline");
		ft_putstr_fd("minishell: syntax error: unexpected end of file \n", 2);
		free (str);
		free(line);
		return (0);
	}
	return (1);
}

int	init_qvar(t_qvar **qvr)
{
	*qvr = (t_qvar *)malloc(sizeof(t_qvar));
	if (!*qvr)
		return (0);
	(*qvr)->result = NULL;
	(*qvr)->str = NULL;
	(*qvr)->rest = NULL;
	return (1);
}

void	join_result(t_qvar	**qvr)
{
	char	*tmp;

	(*qvr)->tmp = ft_strjoin((*qvr)->str, (*qvr)->rest);
	free((*qvr)->str);
	(*qvr)->str = NULL;
	free((*qvr)->rest);
	(*qvr)->rest = NULL;
	tmp = (*qvr)->result;
	(*qvr)->result = ft_strjoin((*qvr)->result, (*qvr)->tmp);
	free(tmp);
	free((*qvr)->tmp);
	(*qvr)->tmp = NULL;
}

void	def_flag_pre(char apr, char c, t_data *nv, t_qvar *qvr)
{
	qvr->type = SQUOTE;
	nv->sqflg = 1;
	if (c == DQUOTES)
	{
		qvr->type = DQUOTES;
		if (apr == '\'')
			nv->dqflg = 3;
		if (apr == '$')
			nv->dqflg = 2;
		else
			nv->dqflg = 1;
		nv->sqflg = 0;
	}
}

void	restofcond(char *cmd, int *i, t_data *nv)
{
	if (cmd[(*i) - 1] == '$')
		nv->dqflg = 3;
	(*i)++;
	if ((cmd[(*i)] == '$' && cmd[(*i) - 1] == DQUOTES
			&& cmd[(*i) + 1] == DQUOTES))
		nv->dqflg = 3;
}

char	*get_str1(char *cmd, int *i, t_cmd *l, t_data *nv)
{
	t_qvar	*qvr;
	char	*str;

	if (!init_qvar(&qvr))
		return (NULL);
	while (cmd[*i] && cmd[*i] != ' ')
	{
		if (cmd[*i] == SQUOTE || cmd[*i] == DQUOTES)
		{
			if (l->herd == 0)
				l->herd = 1;
			def_flag_pre(cmd[(*i) + 1], cmd[*i], nv, qvr);
			restofcond(cmd, i, nv);
			qvr->str = get_inside_quotes(cmd, i, qvr->type);
			(*i)++;
		}
		if (cmd[*i] && is_alpha(cmd[*i]))
			qvr->rest = get_outside_quotes(cmd, i);
		join_result(&qvr);
	}
	str = qvr->result;
	free (qvr);
	return (str);
}

char	*get_str2(char *cmd, int *i, t_data *nv, t_cmd *l)
{
	char	*str;

	str = NULL;
	l->herd = -1;
	str = get_redirection(cmd, &(*i));
	if (ft_strlen(str) > 2 || ft_strlen(str) < 1)
	{
		error_str(str, nv);
		free(str);
		return (NULL);
	}
	if (ft_strlen(str) == 2 && str[0] == '<' && str[1] == '<')
		l->herd = 0;
	return (str);
}
