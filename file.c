/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araiteb <araiteb@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:34:27 by araiteb           #+#    #+#             */
/*   Updated: 2023/10/02 11:43:59 by araiteb          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*---check_file-----*/
int	error_openfile(int fl, t_data *nv)
{
	if (fl == -1)
	{
		nv->exit_status = 1;
		perror ("open");
		close(fl);
		return (-1);
	}
	return (1);
}

int	ft_check_fils(t_check *tmp, t_data *nv, t_cmd *ls)
{
	int		fl;

	(void) ls;
	fl = 0;
	if (access(tmp->name_fd, F_OK) == -1 || access(tmp->name_fd, R_OK) == -1
		|| access(tmp->name_fd, W_OK) == -1)
	{
		if (tmp->mode == (O_RDWR | O_CREAT | O_TRUNC)
			|| tmp->mode == (O_RDWR | O_CREAT | O_APPEND))
		{
			if (tmp->permession)
			{
				fl = open(tmp->name_fd, tmp->mode, tmp->permession);
				if (error_openfile(fl, nv) == -1)
					return (-1);
			}
		}
	}
	else
	{
		fl = open(tmp->name_fd, tmp->mode);
		if (error_openfile(fl, nv) == -1)
			return (-1);
	}
	return (fl);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*dst;
	unsigned char	*sr;

	i = 0;
	dst = (unsigned char *)s1;
	sr = (unsigned char *)s2;
	while (((dst[i] != '\0') || (sr[i] != '\0')) && i < n)
	{
		if (dst[i] < sr[i])
			return (-1);
		else if (dst[i] > sr[i])
			return (1);
		i++;
	}
	return (0);
}
