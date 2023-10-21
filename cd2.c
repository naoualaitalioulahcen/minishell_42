/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 07:18:17 by nait-ali          #+#    #+#             */
/*   Updated: 2023/09/27 04:32:06 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	help_cd(char *to, t_data *nv)
{
	if (!cd_not_exist_directory(to, nv))
		return (0);
	else 
		change_directories(to, nv);
	return (1);
}
