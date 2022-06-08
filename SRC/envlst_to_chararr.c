/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst_to_chararr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 19:01:43 by dkim2             #+#    #+#             */
/*   Updated: 2022/06/08 19:31:42 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/minishell.h"
#include <stdlib.h>

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
		envp[i] = ft_calloc((ft_strlen(curr->key) + ft_strlen(curr->value) + 2), 1);
		if (envp[i] == NULL)
		{
			ft_double_free(envp);
			return (NULL);
		}
		ft_strlcpy(envp[i], curr->key, ft_strlen(curr->key) + 1);
		envp[i][ft_strlen(curr->key)] = '=';
		ft_strlcpy(envp[i] + ft_strlen(curr->key) + 1, curr->value, \
					ft_strlen(curr->value) + 1);
		curr = curr->nextnode;
	}
	return (envp);
}