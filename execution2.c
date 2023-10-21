/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 02:48:32 by araiteb           #+#    #+#             */
/*   Updated: 2023/10/04 19:13:45 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	help_herd_rd_in(t_substruct **cmd, t_cmd *ls, t_data *nv)
{
	if ((*cmd)->next)
		(*cmd) = (*cmd)->next;
	here_doc("tmp", (*cmd)->data, nv, ls);
	ls->filein = open("tmp", O_RDONLY, 0644);
}

int	herd_rd_in(t_cmd *ls, t_substruct **cmd, t_data *nv)
{
	char	*new;

	if ((*cmd)->type == heredoc)
		help_herd_rd_in(cmd, ls, nv);
	else
	{
		new = subc_quots((*cmd)->next->data);
		if (access(new, F_OK) == -1)
			return (free(new), message_error("minishell : ", new, \
			": No such file or directory\n"), nv->exit_status = 1, 0);
		else
		{
			ls->filein = open(new, O_RDONLY, 0644);
			if (ls->filein == -1)
				return (free(new), perror("open"), close(ls->filein), 0);
		}
		ft_free_str(new);
	}
	return (1);
}

char	*getlastcmd(t_cmd *cmd)
{
	t_cmd		*cm;
	t_substruct	*subs;
	char		*str;

	cm = cmd;
	if (cm)
	{
		subs = cm->s_substruct;
		while (subs->next)
			subs = subs->next;
		if (subs->prev && (subs->prev->type == rd_output || \
		(subs->prev->prev && subs->prev->type == rd_output \
		&& subs->prev->prev->type == rd_output)))
		{
			str = ft_strdup(subs->data);
			return (str);
		}
	}
	return (NULL);
}

void	help_get_rd(t_substruct **cmd, t_tmp *var, t_data *nv)
{
	char	*new;
	t_check	tmp;

	close(var->fds[var->ls->i][1]);
	new = subc_quots((*cmd)->next->data);
	tmp.name_fd = new;
	tmp.permession = 0644;
	if ((*cmd)->type == rd_output)
	{
		tmp.mode = (O_RDWR | O_CREAT | O_APPEND);
		var->ls->fileout = ft_check_fils(&tmp, nv, var->ls);
	}
	else
	{
		tmp.mode = (O_RDWR | O_CREAT | O_APPEND);
		var->ls->fileout = ft_check_fils(&tmp, nv, var->ls);
	}
	ft_free_str(new);
}

int	help_get_rd2(t_tmp *var, t_substruct **cmd, t_data *nv)
{
	if (var->ls->i > 0 && var->fds[var->ls->i - 1][0])
		close(var->fds[var->ls->i - 1][0]);
	if (!herd_rd_in(var->ls, cmd, nv) || g_flag_signal == 1)
		return (nv->exit_status = 1, 0);
	return (1);
}
