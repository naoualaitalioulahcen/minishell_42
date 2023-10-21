/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 04:13:02 by araiteb           #+#    #+#             */
/*   Updated: 2023/10/04 20:03:57 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dup(t_cmd *ls, char **option, char **env, t_data *nv)
{
	if (option)
		expand_env_variable(option, env, nv);
	ft_close (ls);
	ls->filein = 0;
	ls->fileout = 1;
	if (check_builtins(ls, option, env, nv))
		exit (0);
	exec_chile (option, env, ls, nv);
}

int	init_var(t_varn **var, t_cmd *list, t_data *nv)
{
	(*var) = (t_varn *)malloc(sizeof(t_varn));
	if (!*var)
		return (0);
	(*var)->i = 0;
	(*var)->size = ft_lstsize(list);
	(*var)->fds = (int **)malloc(sizeof(int *) * ((*var)->size));
	if (!(*var)->fds)
		return (0);
	(*var)->pd = (int *)malloc(sizeof(int) * ((*var)->size));
	if (!(*var)->pd)
		return (0);
	ft_creat_pipe(ft_lstsize(list), (*var)->fds, nv);
	return (1);
}

int	instrc_chile(t_varn *var, t_cmd *tmp, char **env, t_data *nv)
{
	if (var->option)
	{
		var->pd[var->i] = fork();
		if (var->pd[var->i] == -1)
		{
			write (2, "error\n", 7);
			nv->exit_status = 1;
			return (0);
		}
		if (var->pd[var->i] == 0)
		{
			signal (SIGQUIT, SIG_DFL);
			signal (SIGINT, SIG_DFL);
			dup2 (tmp->filein, 0);
			dup2 (tmp->fileout, 1);
			if (var->fds)
				ft_free_matrix(var->fds, var->size);
			ft_dup (tmp, var->option, env, nv);
		}
		ft_free (var->option);
	}
	return (1);
}

int	one_built(t_varn *var, t_cmd *tmp, char **env, t_data *nv)
{
	t_substruct	*tmps;

	var->option = NULL;
	tmps = tmp->s_substruct;
	get_option(&(var->option), tmps);
	tmps = tmp->s_substruct;
	if (!checkrd(tmp, tmps, var->fds, nv) || g_flag_signal == 1)
	{
		if (var->fds)
			ft_free_matrix(var->fds, var->size);
		free (var->pd);
		ft_free (var->option);
		nv->exit_status = 1;
		return (0);
	}
	if (!tmp->prev && !tmp->next && check_builtins(tmp, var->option, env, nv))
	{
		if (var->fds)
			ft_free_matrix(var->fds, var->size);
		free (var->pd);
		ft_free (var->option);
		return (0);
	}
	return (1);
}

void	ft_execution(t_cmd *list, char **env, t_data *nv)
{
	t_cmd		*tmp;
	t_varn		*var;

	tmp = list;
	if (g_flag_signal == 5)
		nv->exit_status = 1;
	if (!init_var(&var, list, nv))
		return ;
	while (tmp && var->i < ft_lstsize(list))
	{
		if (!one_built(var, tmp, env, nv))
		{
			free (var);
			return ;
		}
		var->pd[var->i] = -1;
		if (!instrc_chile(var, tmp, env, nv))
			break ;
		ft_close (tmp);
		if (tmp)
			tmp = tmp->next;
		var->i++;
	}
	wait_pd(var, ft_lstsize(list), nv);
	free_execution(var, list);
}
