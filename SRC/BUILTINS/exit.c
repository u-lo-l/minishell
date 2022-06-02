/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 17:34:28 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/02 11:30:29 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <sys/errno.h>
#include <stdlib.h>

void	do_exit(t_token_list *toklst, t_env *envlst)
{
	int		i;
	int		exit_num;
	char	*exit_str;

	if (!toklst || !toklst->head || ft_strncmp(toklst->head->text, "exit", 5))
		return ;
	if (toklst->head->next == NULL)
		exit(0);
	if (toklst->head->next->next != NULL)
	{
		ft_putstr_fd("minishell : exit : too many args\n", 2);
		envlst->error = 1;
	}
	else
	{
		exit_str = toklst->head->next->text;
		i = -1;
		while (exit_str[++i])
		{
			if (!ft_isdigit(exit_str[i]) && !ft_strchr("-+", exit_str[0]))
			{
				ft_putstr_fd("minishell : exit : numeric arg required\n", 2);
				exit(2);
			}
		}
		exit_num = ft_atoi(exit_str);
		exit(exit_num);
	}
}
