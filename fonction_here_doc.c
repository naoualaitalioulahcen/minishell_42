/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonction_here_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 14:41:59 by araiteb           #+#    #+#             */
/*   Updated: 2023/10/02 12:16:41 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_herdoc(int sig)
{
	(void)sig;
	g_flag_signal = 1;
	close (0);
}

int	help(char *tmps, t_data *nv, t_cmd *ls)
{
	int		fl;
	t_check	tmp;

	signal (SIGINT, sigint_herdoc);
	tmp.name_fd = tmps;
	tmp.mode = (O_CREAT | O_RDWR | O_TRUNC);
	tmp.permession = 0644;
	fl = ft_check_fils(&tmp, nv, ls);
	return (fl);
}

void	help2(char *str, int fl, t_cmd *l, t_data *nv)
{
	char	**ptr;
	char	*tmp;

	ptr = get_env_values(nv->environement);
	if (check_doll(str, '$') && l->herd != 1)
	{
		tmp = str;
		str = option_expand(tmp, ptr, nv);
		free(str);
	}
	write(fl, str, ft_strlen(str));
	write(fl, "\n", 1);
	free_env_values(ptr);
}

void	help3(char *str, int fd, t_data *nv)
{
	(void)nv;
	free (str);
	if (g_flag_signal == 1)
		dup2 (fd, 0);
}

void	here_doc(char *tmps, char *end, t_data *nv, t_cmd *ls)
{
	int		fl;
	char	*str;
	int		fd;

	fd = dup(0);
	fl = help(tmps, nv, ls);
	str = readline("> ");
	if (!ft_strcmp(end, " "))
		write(fl, str, ft_strlen(str));
	while (str && ft_strcmp(str, end))
	{
		help2(str, fl, ls, nv);
		if (str)
			free (str);
		str = readline("> ");
		if (!str)
		{
			ft_free_str(str);
			break ;
		}
	}
	help3(str, fd, nv);
	close (fd);
	close (fl);
}
