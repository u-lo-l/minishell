/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst_to_chararr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:01:43 by dkim2             #+#    #+#             */
/*   Updated: 2022/06/09 12:55:25 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/minishell.h"
#include <stdlib.h>

static char	*attach_keyvalue(char *key, char *value)
{
	int		keylen;
	int		vallen;
	char	*key_and_value;

	keylen = ft_strlen(key);
	vallen = ft_strlen(value);
	key_and_value = ft_calloc(1, keylen + vallen + 2);
	if (key_and_value == NULL)
		return (NULL);
	ft_strlcpy(key_and_value, key, keylen + 1);
	key_and_value[keylen] = '=';
	ft_strlcpy(key_and_value + keylen + 1, value, vallen + 1);
	return (key_and_value);
}

char	**envlst_to_arr(t_env *envlst)
{
	t_envnode	*curr;
	char		**envp;
	int			i;

	if (envlst == NULL)
		return (NULL);
	envp = ft_calloc(envlst->element + 1, sizeof(char *));
	if (envp == NULL)
		return (NULL);
	i = -1;
	curr = envlst->phead;
	while (++i < envlst->element)
	{
		envp[i] = attach_keyvalue(curr->key, curr->value);
		if (envp[i] == NULL)
		{
			ft_double_free(envp);
			return (NULL);
		}
		curr = curr->nextnode;
	}
	return (envp);
}
