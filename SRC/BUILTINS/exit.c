/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyoo <yyoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 17:34:28 by yyoo              #+#    #+#             */
/*   Updated: 2022/05/30 18:56:18 by yyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <sys/errno.h>
#include <stdlib.h>

void	do_exit(t_token_list *token)
{
	if (!token | !ft_cmp(token->head->text, "exit"))
		return ;
	exit(errno);
}
