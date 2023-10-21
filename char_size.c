/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 04:07:40 by araiteb           #+#    #+#             */
/*   Updated: 2023/09/21 03:47:03 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_size_tab(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	**__resize(char **Array, char *new)
{
	int		len;
	char	**tmp;
	int		i;

	if (!Array)
		len = 0;
	else
		len = ft_size_tab(Array);
	tmp = (char **)malloc(sizeof(char *) * (len + 2));
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < len)
	{
		tmp[i] = ft_strdup(Array[i]);
		i++;
	}
	tmp[len] = ft_strdup(new);
	tmp[len + 1] = NULL;
	ft_free(Array);
	return (tmp);
}

void	ft_close_pipe(t_cmd *ls, int **fds)
{
	int	i;

	i = 0;
	while (i < ft_lstsize(ls))
	{
		close (fds[i][0]);
		close (fds[i][1]);
		i++;
	}
}
