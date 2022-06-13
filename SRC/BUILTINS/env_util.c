/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:51:37 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/13 22:47:39 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdlib.h>

int	add_node_to_lst(t_env *envlst, t_envnode *node)
{
	if (!node || !envlst)
		return (FALSE);
	if (envlst->element == 0)
		envlst->phead = node;
	else
	{
		node->prevnode = envlst->ptail;
		envlst->ptail->nextnode = node;
	}
	envlst->ptail = node;
	node->nextnode = NULL;
	envlst->element++;
	return (TRUE);
}

int	del_node_from_lst(t_env *envlst, char *key)
{
	t_envnode	*curr_node;

	if (!envlst || !key)
		return (FALSE);
	curr_node = envlst->phead;
	while (curr_node)
	{
		if (!ft_strncmp(curr_node->key, key, ft_strlen(key) + 1))
		{
			if (curr_node->prevnode == NULL)
				envlst->phead = curr_node->nextnode;
			if (curr_node->nextnode == NULL)
				envlst->ptail = curr_node->prevnode;
			if (curr_node->prevnode != NULL)
				curr_node->prevnode->nextnode = curr_node->nextnode;
			if (curr_node->nextnode != NULL)
				curr_node->nextnode->prevnode = curr_node->prevnode;
			free_env_node(curr_node);
			envlst->element--;
			break ;
		}
		curr_node = curr_node->nextnode;
	}
	return (TRUE);
}

int	modify_value(t_env *envlst, char *key, char *value)
{
	t_envnode	*node;
	int			keylen;

	if (!envlst || !key)
		return (FALSE);
	keylen = ft_strlen(key);
	node = envlst->phead;
	while (node)
	{
		if (ft_strncmp(key, node->key, keylen + 1) == 0)
		{
			free(node->value);
			node->value = ft_strdup(value);
			return (TRUE);
		}
		node = node->nextnode;
	}
	return (FALSE);
}

void	print_one_env(t_envnode *node, char value_c)
{
	if (!node)
		return ;
	if (node->key)
		ft_putstr_fd(node->key, 1);
	if (node->value)
	{
		ft_putchar_fd('=', 1);
		if (value_c)
			ft_putchar_fd(value_c, 1);
		ft_putstr_fd(node->value, 1);
		if (value_c)
			ft_putchar_fd(value_c, 1);
	}
	ft_putstr_fd("\n", 1);
}

int	seperate_keyvalue(char *k_and_v, char **emptykey, char **emptyval)
{
	char		*equal_char;

	if (!k_and_v || *emptykey || *emptyval)
		return (FALSE);
	equal_char = ft_strchr(k_and_v, '=');
	if (equal_char == NULL)
		return (FALSE);
	*emptykey = ft_strndup(k_and_v, equal_char - k_and_v);
	*emptyval = ft_strndup(equal_char + 1, ft_strlen(equal_char + 1));
	if (!*emptykey || !*emptyval)
	{
		free(*emptykey);
		free(*emptyval);
		return (FALSE);
	}
	return (TRUE);
}
