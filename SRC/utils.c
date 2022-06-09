/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:29:32 by dkim2             #+#    #+#             */
/*   Updated: 2022/06/10 01:14:47 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/minishell.h"
#include <stdlib.h>

void	ft_double_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	return_err(char *errstr, int ret_val)
{
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(errstr, 2);
	ft_putstr_fd("\n", 2);
	return (ret_val);
}

int	is_env_name(char *name)
{
	int	i;

	if (!name)
		return (FALSE);
	i = 0;
	if (name[i] != '_' && ft_isalpha(name[i]) != TRUE)
		return (FALSE);
	while (name[++i])
	{
		if (ft_isalnum(name[i]) == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

int	get_child_exit_status(int stat_loc)
{
	if ((stat_loc & 0xFF) == 0)
		return ((stat_loc >> 8) & 0xFF);
	else if ((stat_loc & 0xFF) == 0x7f)
		return (((stat_loc >> 8) & 0xFF) + 0x80);
	else
		return ((stat_loc & 0xFF) + 0x80);
}
