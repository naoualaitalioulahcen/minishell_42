/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   les_outiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 01:22:06 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/27 03:58:59 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*ch;

	ch = (unsigned char *)s;
	while (*ch != (char)c)
	{
		if (*ch == '\0')
		{
			return (NULL);
		}
		ch++;
	}
	return ((char *)ch);
}

int	message_erreur(char *str, t_data *nv)
{
	ft_putstr_fd("minisell : exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	nv->exit_status = 255;
	return (nv->exit_status);
}

int	ft_atoi(char *str, t_data *nv)
{
	unsigned long long	res;
	int					n;
	int					sign;

	res = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		n = res;
		res = res * 10 + (*str - 48);
		if ((res > 9223372036854775807U && sign == 1) \
		|| (sign == -1 && res > 9223372036854775808U))
			return (message_erreur(str, nv));
		str++;
	}
	nv->exit_status = res * sign;
	return (res * sign);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s || fd < 0)
		return ((void)0);
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
