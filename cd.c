/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:32:11 by nait-ali          #+#    #+#             */
/*   Updated: 2023/10/04 20:40:56 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_home(t_data *nv)
{
	t_environement	*tmp;

	tmp = nv->environement;
	while (tmp) 
	{
		if (ft_strcmp(tmp->cle, "HOME") == 0)
			return (tmp->valeur);
		tmp = tmp->next;
	}
	ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	nv->exit_status = 1;
	return (NULL);
}

void	search_pwd(char *pwd, t_data *nv)
{
	t_environement	*tmp;
	char			*pwd_;

	tmp = nv->environement;
	while (tmp)
	{
		if (!ft_strcmp(tmp->cle, "PWD"))
		{
			free(tmp->valeur);
			tmp->valeur = ft_strdup(pwd);
			free(tmp->env);
			pwd_ = ft_strjoin(tmp->cle, "=");
			tmp->env = ft_strjoin(pwd_, tmp->valeur);
			free(pwd_);
		}
		tmp = tmp->next;
	}
}

void	search_oldpwd(char *oldpwd, t_data *nv)
{
	t_environement	*tmp;
	char			*oldpwd_;
	char			*var;

	tmp = nv->environement;
	var = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->cle, "OLDPWD"))
		{
			free(tmp->valeur);
			tmp->valeur = ft_strdup(oldpwd);
			var = tmp->valeur;
			free(tmp->env);
			oldpwd_ = ft_strjoin(tmp->cle, "=");
			tmp->env = ft_strjoin(oldpwd_, tmp->valeur);
			free(oldpwd_);
		}
		tmp = tmp->next;
	}
}

void	change_directories(char *pwd, t_data *nv)
{
	t_environement	*tmp;
	char			*tt;

	tmp = nv->environement;
	while (tmp)
	{
		if (ft_strcmp(tmp->cle, "PWD") == 0)
			tt = tmp->valeur;
		tmp = tmp->next;
	}
	search_oldpwd(tt, nv);
	search_pwd(pwd, nv);
	free(pwd);
}

void	ft_cd(t_cmd *cmd, char **option, t_data *nv)
{
	char		*to;
	t_substruct	*var ;

	var = cmd->s_substruct->next;
	if (!var || !ft_strcmp(var->data, "~")) 
	{
		to = find_home(nv);
		if (!to)
			return ;
	}
	if (var && ft_strcmp(var->data, "~")) 
		to = option[1];
	if (!chedir_error(to, nv)) 
		return ;
	to = getcwd(NULL, PATH_MAX);
	if (!cd_not_exist_directory(to, nv))
		return ;
	else 
		change_directories(to, nv);
	nv->exit_status = 0;
}
