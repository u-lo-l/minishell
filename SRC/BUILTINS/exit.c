/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyoo <yyoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 17:34:28 by yyoo              #+#    #+#             */
/*   Updated: 2022/05/28 17:35:10 by yyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <sys/errno.h>
#include <stdlib.h>

void	do_exit(char *token)
{
	if (!token | !ft_cmp(token, "exit"))
		return ;
	exit(errno);
}
