/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:32:39 by dkim2             #+#    #+#             */
/*   Updated: 2022/06/11 16:22:50 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdlib.h>

t_token_list	*create_empty_toklst(void)
{
	t_token_list	*lst;

	lst = ft_calloc(1, sizeof(t_token_list));
	return (lst);
}

void	free_toklst(t_token_list *lst)
{
	t_token	*curr;
	t_token	*next;

	if (!lst)
		return ;
	curr = lst->head;
	while (curr)
	{
		next = curr->next;
		free_token(curr);
		curr = next;
	}
	free(lst);
}

int	add_token_to_toklst(t_token_list *lst, t_token *tok)
{
	if (lst == NULL || tok == NULL)
		return (FALSE);
	if (lst->head == NULL)
		lst->head = tok;
	if (lst->tail != NULL)
		lst->tail->next = tok;
	lst->tail = tok;
	lst->num_of_tokens++;
	return (TRUE);
}
