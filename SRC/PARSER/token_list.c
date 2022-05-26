/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:32:39 by dkim2             #+#    #+#             */
/*   Updated: 2022/05/26 19:57:06 by dkim2            ###   ########.fr       */
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
	// printf("addling token to list : %d: %s\n", tok->type, tok->text);
	if (lst->head == NULL)
		lst->head = tok;
	if (lst->tail != NULL)
		lst->tail->next = tok;
	lst->tail = tok;
	lst->num_of_tokens++;
	return (TRUE);
}

static void print_token_type(enum e_token_type type)
{
	if (type == e_eof)
		printf("e_eof");
	else if (type == e_pipeline)
		printf("e_pipeline");
	else if (type == e_word)
		printf("e_word");
	else if (type == e_inrdr)
		printf("e_inrdr");
	else if (type == e_outrdr)
		printf("e_outrdr");
	else if (type == e_appendrdr)
		printf("e_appendrdr");
	else if (type == e_heredoc)
		printf("e_heredoc");
	else if (type == e_exitstatus)
		printf("e_exitstatus");
}

void	print_token_list(t_token_list *lst)
{
	t_token	*curr;

	if (lst)
	{	
		curr = lst->head;
		printf("%d tokens |", lst->num_of_tokens);
		while (curr)
		{
			if (is_eof_token(curr))
				printf("EOF_TOK\n");
			else
			{
				printf("\033[2m->\033[0m");
				printf("[");
				print_token_type(curr->type);
				printf(":%s]", curr->text);
			}
			curr = curr->next;
		}
	}
	printf("\n");
}
