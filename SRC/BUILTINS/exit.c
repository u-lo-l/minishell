/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 17:34:28 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/01 23:04:28 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <sys/errno.h>
#include <stdlib.h>

void	do_exit(t_token_list *token)
{
	char	*exit_str;
	int		i;
	int		exit_num;

	if (!token)
		return ;
	if (!ft_strncmp(token->head->text, "exit", 5))
		return ;
	if (token->next == NULL)
		exit(0);
	if (token->next->next != NULL)
		ft_putstr_fd("minishell : exit : too many arguments" , 2);
	else
	{
		exit_str = token->next->text;
		i = -1;
		while (exit_str[++i])
			if (ft_isdigit(exit_str[i]) == FALSE)
			{
				ft_putstr_fd("minishell : exit : numeric argument required" , 2);
				exit(2);
			}
		exit_num = ft_atoi(exit_str);
		exit(exit);
	}
}
