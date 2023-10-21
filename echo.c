/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:32:22 by nait-ali          #+#    #+#             */
/*   Updated: 2023/10/04 18:47:57 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_new_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (str[i] == '-' && str[i + 1])
	{
		i++;
		while (str[i] == 'n')
			i++;
	}
	if (str[i])
		return (0);
	return (1);
}

void	help_ftecho(t_cmd *ls, char **option, t_substruct *cmd, int i)
{
	(void) cmd;
	while (option[i])
	{
		ft_putstr_fd(option[i], ls->fileout);
		i++;
		if (option[i])
			write(ls->fileout, " ", 1);
	}
}

void	ft_echo(t_cmd *ls, char **option, t_data *nv)
{
	int			var;
	t_substruct	*cmd;
	int			i;

	var = 0;
	cmd = ls->s_substruct->next;
	i = 1;
	while (option[i] && cmd && \
	check_new_line(option[i]))
	{
		if (ft_strlen(cmd->data))
		{
			var = 1;
			i++;
		}
		else
			break ;
	}
	help_ftecho(ls, option, cmd, i);
	if (!var)
		write(ls->fileout, "\n", 1);
	nv->exit_status = 0;
}
