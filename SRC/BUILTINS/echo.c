/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:51:17 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/11 16:11:18 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

int	do_echo(t_token_list *echo_token)
{
	t_token	*curr;
	int		no_option_n;

	no_option_n = TRUE;
	curr = echo_token->head;
	if (ft_strncmp(curr->text, "echo", 5))
		return (return_err("echo : unexpected error", 1));
	curr = curr->next;
	if (curr != NULL)
	{
		no_option_n = ft_strncmp(curr->text, "-n", 3);
		if (no_option_n == FALSE)
			curr = curr->next;
		while (curr)
		{
			ft_putstr_fd(curr->text, 1);
			if (curr->next)
				ft_putchar_fd(' ', 1);
			curr = curr->next;
		}
	}
	if (no_option_n)
		ft_putchar_fd('\n', 1);
	return (0);
}
