/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:51:27 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/11 16:11:22 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"

int	do_env(t_token_list *toklst, t_env *env)
{
	t_envnode	*curr;
	int			i;

	if (env == NULL)
		return (return_err("env : unexpected error", 1));
	if (toklst->head->next != NULL)
		return (return_err("env : minishell doesn't interpret any args", 1));
	curr = env->phead;
	i = 0;
	while (curr)
	{
		print_one_env(curr, 0);
		curr = curr->nextnode;
		if (++i > env->element)
			break ;
	}
	return (0);
}

char	*search_key(t_env *env, char *key)
{
	t_envnode	*curr;

	curr = env->phead;
	while (curr)
	{
		if (!ft_strncmp(curr->key, key, ft_strlen(key) + 1))
			return (curr->value);
		curr = curr->nextnode;
	}
	return ("");
}
