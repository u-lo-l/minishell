/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:32:11 by dkim2             #+#    #+#             */
/*   Updated: 2022/06/11 16:05:25 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/minishell.h"
#include <stdlib.h>

t_envnode	*create_envnode(char *key, char *value)
{
	t_envnode	*node;

	if (!key)
		return (NULL);
	node = ft_calloc(1, sizeof(t_envnode));
	node->key = ft_strdup(key);
	if (!key)
	{
		free(node);
		return (NULL);
	}
	node->value = ft_strdup(value);
	return (node);
}

t_env	*env_list(char **env)
{
	t_env		*envlst;
	t_envnode	*node;
	char		*k_and_v[2];

	if (!env)
		return (NULL);
	envlst = ft_calloc(1, sizeof(t_env));
	if (!envlst)
		return (NULL);
	while (TRUE)
	{
		k_and_v[0] = 0;
		k_and_v[1] = 0;
		if (!seperate_keyvalue(env[envlst->element], &k_and_v[0], &k_and_v[1]))
			break ;
		node = create_envnode(k_and_v[0], k_and_v[1]);
		free(k_and_v[0]);
		free(k_and_v[1]);
		if (!node || !add_node_to_lst(envlst, node))
			break ;
		if (env[envlst->element] == NULL)
			return (envlst);
	}
	free_env_list(envlst);
	return (NULL);
}

void	free_env_node(t_envnode *node)
{
	if (node == NULL)
		return ;
	free(node->key);
	free(node->value);
	free(node);
}

void	free_env_list(t_env *envlst)
{
	t_envnode	*curr;
	t_envnode	*next;

	if (envlst == NULL)
		return ;
	curr = envlst->phead;
	while (curr != NULL)
	{
		next = curr->nextnode;
		free_env_node(curr);
		curr = next;
	}
	free(envlst);
}
