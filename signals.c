/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 00:24:01 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/28 01:24:36 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_handler(int sig)
{
	(void)sig;
	if (waitpid(0, NULL, WNOHANG))
	{
		ft_putstr_fd("\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_flag_signal = 5;
	}
}

void	init_signals(void)
{
	g_flag_signal = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, my_handler);
}

void	signals_in_child_process(int status, t_data *nv)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("\\Quit: 3\n", 1);
		if (WTERMSIG(status) == SIGINT)
			ft_putstr_fd("\n", 1);
		if (WTERMSIG(status) == 11)
			ft_putstr_fd("Segmentation fault: 11\n", 2);
		nv->exit_status = WTERMSIG(status) + 128;
	}
	else 
		nv->exit_status = WEXITSTATUS(status);
}
