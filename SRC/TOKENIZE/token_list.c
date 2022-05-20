#include "../../INC/minishell.h"

t_token_list	*create_empty_toklst(void)
{
	t_token_list *lst;

	lst = ft_calloc(1, sizeof(t_token_list));
	return (lst);
}

void	free_toklist(t_token_list *lst)
{
	t_token	*curr;
	t_token *next;

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
	if (lst->rear != NULL)
		lst->rear->next = tok;
	lst->rear = tok;
	lst->curr_count++;
	return (TRUE);
}

int	del_token_from_toklst(t_token_list *lst)
{
	if (lst == NULL)
		return (FALSE);
	
}

void	print_token_list(t_token_list *lst)
{
	t_token *curr;
	if (!lst)
		return ;
	printf("==token list==\n");
	curr = lst->head;
	while (curr)
	{
		printf("%s\n", curr->text);
		curr = curr->next;
	}
	printf("==============\n");
}