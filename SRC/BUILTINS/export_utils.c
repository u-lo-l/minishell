/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:32:43 by dkim2             #+#    #+#             */
/*   Updated: 2022/06/11 13:45:01 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdlib.h>

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
	t_envnode	*temp;
	int			i;
	int			c_i;

	i = 1;
	target_node = heap[i];
	heap[i] = heap[curr_elemnt_count];
	while (i * 2 <= curr_elemnt_count)
	{
		c_i = i * 2;
		if (i * 2 < curr_elemnt_count && \
			(ft_strncmp(heap[c_i]->key, heap[c_i + 1]->key, \
			ft_strlen(heap[c_i]->key) + 1) > 0))
			c_i++;
		if (ft_strncmp(heap[i]->key, heap[c_i]->key, \
			ft_strlen(heap[c_i]->key) + 1) < 0)
			break ;
		temp = heap[i];
		heap[i] = heap[c_i];
		heap[c_i] = temp;
		i = c_i;
	}
	return (target_node);
}

int	show_shell_var_asscending(t_env *envlst)
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
		ft_putstr_fd("declare -x : ", 1);
		print_one_env(curr_node, '"');
	}
	free(heap);
	return (TRUE);
}
