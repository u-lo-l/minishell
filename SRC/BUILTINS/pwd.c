/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:51:44 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/11 15:43:32 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdlib.h>
#include <errno.h>

static void	pwd_err(void)
{
	if (errno == EACCES)
		ft_putstr_fd("permission denied\n", 2);
	else if (errno == EFAULT)
		ft_putstr_fd("bad address\n", 2);
	else if (errno == EINVAL)
		ft_putstr_fd("invalid buffer\n", 2);
	else if (errno == ENAMETOOLONG)
		ft_putstr_fd("path name strind exceeds PATH_MAX\n", 2);
	else if (errno == ENOENT)
		ft_putstr_fd("current working dir has been unlinked\n", 2);
	else if (errno == ENOMEM)
		ft_putstr_fd("out of memory\n", 2);
	else if (errno == ERANGE)
		ft_putstr_fd("size arg of getcwd() is less than absolute \
						pathname of the working dir\n", 2);
	else
		ft_putstr_fd("unexpected error\n", 2);
}

int	do_pwd(void)
{
	char	*buff;

	buff = getcwd(NULL, 0);
	if (!buff)
	{
		pwd_err();
		return (1);
	}
	else
	{
		ft_putstr_fd(buff, 1);
		ft_putstr_fd("\n", 1);
		free(buff);
		return (0);
	}
}
