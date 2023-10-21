/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:32:33 by nait-ali          #+#    #+#             */
/*   Updated: 2023/10/04 18:18:10 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	correct_arg(char *num)
{
	int	i;

	i = 0;
	if (num[i] == '-')
		i++;
	while (num[i])
	{
		if (num[i] >= '0' && num[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

void	normal_exit(t_data *nv)
{
	int	i;

	i = nv->exit_status;
	ft_putstr_fd("exit\n", 2);
	nv->exit_status = i;
	exit(nv->exit_status);
}

void	ft_exit(t_cmd *lst, t_data *nv)
{
	if (lst->s_substruct && !lst->s_substruct->next)
		normal_exit(nv);
	else if (!correct_arg(lst->s_substruct->next->data))
	{
		message_error("exit \n", "minishell : exit: ", \
		lst->s_substruct->next->data);
		ft_putstr_fd(": numeric argument required\n", 2);
		nv->exit_status = 255;
		exit (255);
	}
	else if (n_lstsize(lst->s_substruct) > 2)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("minishel: exit: too many arguments\n", 2);
		nv->exit_status = 1;
		return ;
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		exit(ft_atoi((lst->s_substruct->next->data), nv));
	}
}
