/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 17:34:28 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/13 16:18:25 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdlib.h>

static char	*remove_space(char **origin)
{
	char	*trimed;

	if (!*origin)
		return (NULL);
	trimed = ft_strtrim(*origin, " ");
	if (trimed == NULL)
		return (NULL);
	free (*origin);
	*origin = trimed;
	return (*origin);
}

int	do_exit(t_env *envlst, t_token_list *toklst)
{
	int		i;
	int		exit_num;
	char	*exit_str;

	if (!toklst || !toklst->head)
		return (1);
	if (toklst->head->next == NULL)
		exit(envlst->error);
	else
	{
		exit_str = toklst->head->next->text;
		i = -1;
		while (exit_str[++i])
		{
			if (!remove_space(&(exit_str)))
				return (return_err("exit : unexpected error", 1));
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
