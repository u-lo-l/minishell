/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 16:29:32 by dkim2             #+#    #+#             */
/*   Updated: 2022/06/08 16:38:03 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/minishell.h"

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