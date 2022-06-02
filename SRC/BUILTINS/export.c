/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 15:52:00 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/02 09:59:16 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdlib.h>

static void	swap_envnode(t_envnode **pnode1, t_envnode **pnode2)
{
	t_envnode	*temp;

	temp = *pnode1;
	*pnode1 = *pnode2;
	*pnode2 = temp;
}

static int	insert_to_heap(t_envnode **heap, t_envnode *node, int index)
{
	char		*keys[2];
	t_envnode	*temp;

	if (!heap || !node || !node->key)
		return (FALSE);
	heap[index] = node;
	while (index / 2)
	{
		keys[0] = heap[index]->key;
		keys[1] = heap[index / 2]->key;
		if (ft_strncmp(keys[0], keys[1], ft_strlen(keys[0]) + 1) > 0)
			break ;
		temp = heap[index];
		heap[index] = heap[index / 2];
		heap[index / 2] = temp;
		index /= 2;
	}
	return (TRUE);
}

static t_envnode	*pop_from_heap(t_envnode **heap, int curr_elemnt_count)
{
	t_envnode	*target_node;
	int			i;
	int			c_i;

	i = 1;
	target_node = heap[i];
	heap[i] = heap[curr_elemnt_count];
	while (i * 2 <= curr_elemnt_count)
	{
		c_i = i * 2;
		if (i * 2 < curr_elemnt_count)
		{
			if (ft_strncmp(heap[c_i]->key, heap[c_i + 1]->key, \
				ft_strlen(heap[c_i]->key) + 1) > 0)
				c_i++;
		}
		if (ft_strncmp(heap[i]->key, heap[c_i]->key, \
			ft_strlen(heap[c_i]->key) + 1) < 0)
			break ;
		swap_envnode(heap + i, heap + c_i);
		i = c_i;
	}
	return (target_node);
}

static int	show_shell_var_asscending(t_env *envlst)
{
	t_envnode	**heap;
	t_envnode	*curr_node;
	int			heap_elements;

	if (NULL == envlst)
		return (FALSE);
	heap = ft_calloc(envlst->element + 1, sizeof(t_envnode *));
	if (NULL == heap)
		return (FALSE);
	heap_elements = 0;
	curr_node = envlst->phead;
	while (++heap_elements <= envlst->element)
	{
		insert_to_heap(heap, curr_node, heap_elements);
		curr_node = curr_node->nextnode;
	}
	heap_elements = 0;
	while (++heap_elements <= envlst->element)
	{
		curr_node = pop_from_heap(heap, envlst->element - heap_elements + 1);
		printf("export : ");
		print_one_env(curr_node, '"');
	}
	free(heap);
	return (TRUE);
}

/* env_list에 노드를 추가하는 함수 add_node와 비슷하게 동작 함 */
void	do_export(t_token_list *toklst, t_env *envlst)
{
	t_envnode	*newnode;
	t_token		*curr_tok;
	char		*key_and_value[2];

	if (!envlst || !toklst)
		return ;
	if (toklst->num_of_tokens == 1)
	{
		show_shell_var_asscending(envlst);
		return ;
	}
	curr_tok = toklst->head->next;
	while (curr_tok)
	{
		ft_bzero(key_and_value, sizeof(char *) * 2);
		seperate_keyvalue(curr_tok->text, &key_and_value[0], &key_and_value[1]);
		if (!modify_value(envlst, key_and_value[0], key_and_value[1]))
		{
			newnode = create_envnode(key_and_value[0], key_and_value[1]);
			add_node_to_lst(envlst, newnode);
		}
		free(key_and_value[0]);
		free(key_and_value[1]);
		curr_tok = curr_tok->next;
	}
}
/*
int main(int argc, char **argv, char **envp)
{
	t_env *ev;
	char	**token;

	token = malloc(sizeof(char *) * 3);
	token[0] = malloc(sizeof(char) *7);
	token[1] = malloc(sizeof(char) *10);
	token[2] = malloc(sizeof(char) *10);

	(void)argc;
	(void)argv;
	ev = env_list(envp);
	do_env(ev);
	printf("\n#############################################\n\n");
	
	token[0] = "export";
	token[1] = "A=123";
	token[2] = "B=BBBB";
	
	export(ev, token);
	do_env(ev);
	printf("\n#############################################\n\n");
	printf("%s\n", ev->ptail->key);
	printf("element : %d\n", ev->element);
}
*/