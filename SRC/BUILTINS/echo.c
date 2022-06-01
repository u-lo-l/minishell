/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:51:17 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/01 21:27:01 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdlib.h>

void	do_echo(t_token_list *echo_token)
{
	t_token	*curr;
	int		n;

	n = 0;
	curr = echo_token->head;
	if (ft_strncmp(curr->text, "echo", 5))
		return ;
	curr = curr->next;
	if (!ft_strncmp(curr->text, "-n", 3))
	{
		curr = curr->next;
		n = 1;
	}
	while (curr)
	{
		printf("%s", curr->text);
		if (curr->next)
			printf(" ");
		curr = curr->next;
	}
	if (n != 1)
		printf("\n");
}
