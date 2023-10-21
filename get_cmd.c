/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 02:15:44 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/28 05:12:54 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_sps(char **str, t_cmd **list, t_data *nv)
{
	int		i;
	char	*cmd;

	i = 0;
	while (str[i])
	{
		if (str[i] && !ft_strcmp(str[i], " "))
		{
			write (2, "minishell: syntax error near unexpected token `|'\n", 51);
			ft_free(str);
			return (0);
		}
		else
		{
			cmd = ft_strtrim(str[i], " \t");
			ft_lstadd_back(list, ft_lstnew(cmd, nv));
			free (cmd);
		}
		i++;
	}
	return (1);
}

int	help_get_cmds(char *line, t_cmd **list, t_data *nv)
{
	char	**str;
	int		i;
	char	*tmp;

	tmp = ft_strtrim(line, " ");
	str = ft_split(line, '|');
	i = 0;
	if (!str || ft_strcmp(line, "|") == 0
		|| (tmp[0] == '|' && ft_strlen(line) > 1))
	{
		nv->exit_status = 258;
		write (2, "minishell: syntax error near unexpected token `|'\n", 51);
		ft_free(str);
		free(tmp);
		return (0);
	}
	free(tmp);
	if (!check_sps(str, list, nv))
		return (0);
	ft_free(str);
	free(line);
	return (1);
}

void	pr_cmpquot(char c, char type, int *cmp1, int *cmp2)
{
	if (c == type && (*cmp1) == 0)
	{
		if ((*cmp2) != 0)
			(*cmp2) -= 1;
		else
			(*cmp2) += 1;
	}
}

int	non_closed_quotes(char *line)
{
	int	serror;
	int	derror;
	int	i;

	derror = 0;
	serror = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == DQUOTES)
			pr_cmpquot(line[i], DQUOTES, &serror, &derror);
		else if (line[i] == SQUOTE)
			pr_cmpquot(line[i], SQUOTE, &derror, &serror);
		i++;
	}
	if ((serror % 2) || (derror % 2))
	{
		write (2, "Error: unclosed quotes !\n", 25);
		ft_free_str (line);
		return (1);
	}
	return (0);
}

int	get_cmds(char *line, t_cmd **list, t_data *nv)
{
	int		i;

	if (!line_filpip(line))
		return (nv->exit_status = 258, 0);
	i = 0;
	while (line[i])
	{
		if (line[i] == '|' && line[i + 1] == '|' && line[i + 2] == '|')
		{
			ft_putstr_fd("minishell: syntax error ", 2);
			ft_putstr_fd("near unexpected token `||'\n", 2);
			ft_free_str(line);
			return (nv->exit_status = 258, 0);
		}
		i++;
	}
	if (!help_get_cmds(line, list, nv))
	{
		ft_free_str(line);
		return (nv->exit_status = 258, 0);
	}
	return (1);
}
