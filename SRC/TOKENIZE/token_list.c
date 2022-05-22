/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:32:39 by dkim2             #+#    #+#             */
/*   Updated: 2022/05/22 18:37:50 by dkim2            ###   ########.fr       */
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
	lst->curr_count++;
	return (TRUE);
}

int	del_token_from_toklst(t_token_list *lst)
{
	if (lst == NULL)
		return (FALSE);
	return (TRUE);
}

void	print_token_list(t_token_list *lst)
{
	t_token	*curr;

	if (!lst)
		return ;
	printf("==token list==\n");
	curr = lst->head;
	while (curr)
	{
		if (is_eof_token(curr))
			printf("EOF_TOK\n");
		else
			printf("┏text: <%s>\n┗len : %d\n", curr->text, curr->text_len);
		curr = curr->next;
	}
	printf("==============\n");
}
