/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:44:28 by araiteb           #+#    #+#             */
/*   Updated: 2023/10/04 18:19:51 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_flag_signal;

int	check_linesps(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\f'
			&& line[i] != '\v' && line[i] != '\n' && line[i] != '\r' )
			return (1);
		i++;
	}
	return (0);
}

int	check_builtins(t_cmd *cmd, char **option, char **env, t_data *nv)
{
	expand_env_variable(option, env, nv);
	if (cmd->s_substruct && !ft_strcmp("pwd", cmd->s_substruct->data))
		return (ft_pwd(cmd, nv), 1);
	if (cmd->s_substruct && !ft_strcmp("echo", cmd->s_substruct->data))
		return (ft_echo(cmd, option, nv), 1);
	if (cmd->s_substruct && !ft_strcmp("env", cmd->s_substruct->data))
		return (ft_env(cmd, nv), 1);
	if (cmd->s_substruct && !ft_strcmp("exit", cmd->s_substruct->data))
		return (ft_exit(cmd, nv), 1);
	if (cmd->s_substruct && !ft_strcmp("unset", cmd->s_substruct->data))
		return (ft_unset(cmd, nv, option), 1);
	if (cmd->s_substruct && !ft_strcmp("cd", cmd->s_substruct->data))
		return (ft_cd(cmd, option, nv), 1);
	if (cmd->s_substruct && !ft_strcmp("export", cmd->s_substruct->data))
		return (ft_export(cmd, option, nv), 1);
	return (0);
}

void	free_env_values(char **env_values)
{
	int	i;

	i = 0;
	while (env_values[i])
	{
		free (env_values[i]);
		i++;
	}
	free (env_values);
}

void	help_main( char *line, char **ptr, t_cmd *list, t_data *nv)
{
	if (!line)
		(write(1, "exit\n", 5), nv->exit_status = 0, exit(nv->exit_status));
	ptr = get_env_values(nv->environement);
	if (ft_strlen(line))
	{
		add_history(line);
		if (get_cmds(line, &list, nv) && syntaxe_error(list, nv))
			ft_execution(list, ptr, nv);
		free_env_values(ptr);
		free_list (&list);
	}
	else
	{
		free(line);
		free_env_values(ptr);
	}
}

int	main(int ac, char **av, char **env)
{
	char			*line;
	t_cmd			*list;
	char			**ptr;
	t_data			nn;

	line = NULL;
	list = NULL;
	ptr = NULL;
	if (ac != 1)
		return (message_error("minishell: ", av[1], \
		": No such file or directory\n"), 0);
	init_environement(env, &nn);
	while (1)
	{
		init_signals();
		line = readline(LINE);
		help_main(line, ptr, list, &nn);
	}
	free_environement(&nn);
	return (0);
}
