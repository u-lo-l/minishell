/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 17:34:28 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/11 16:53:24 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdlib.h>

int	do_exit(t_token_list *toklst)
{
	int		i;
	int		exit_num;
	char	*exit_str;

	if (!toklst || !toklst->head)
		return (1);
	if (toklst->head->next == NULL)
		exit(0);
	else
	{
		exit_str = toklst->head->next->text;
		i = -1;
		while (exit_str[++i])
		{
			while (exit_str[i] == ' ')
				i++;
			if (!ft_isdigit(exit_str[i]) && !ft_strchr("-+", exit_str[0]))
				exit (return_err("exit : numeric arg required", 255));
		}
		if (toklst->head->next->next != NULL)
			return (return_err("exit : too many args", 1));
		exit_num = ft_atoi(exit_str);
		exit(exit_num);
	}
	return (0);
}
