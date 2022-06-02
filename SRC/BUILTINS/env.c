/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:51:27 by yyoo              #+#    #+#             */
/*   Updated: 2022/06/02 11:33:11 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../../INC/minishell.h"

void	do_env(t_env *env)
{
	t_envnode	*curr;

	curr = env->phead;
	while (curr)
	{
		print_one_env(curr, 0);
		curr = curr->nextnode;
	}
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

// int main(int argc, char **argv, char **envp)
// {
// 	t_env	*env;
// 	char	*str = "HOME";

// 	(void)argc;
// 	(void)argv;
// 	env = do_env(envp);
// 	printf("\n%s\n", search_key(env, str));
// }
