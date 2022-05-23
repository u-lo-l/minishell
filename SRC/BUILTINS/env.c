/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyoo <yyoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:51:27 by yyoo              #+#    #+#             */
/*   Updated: 2022/05/23 13:51:30 by yyoo             ###   ########.fr       */
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
		printf("%s", curr->key);
		printf("=");
		printf("%s\n", curr->value);
		curr = curr->nextnode;
	}
}

char	*search_key(t_env *env, char *key)
{
	t_envnode	*curr;

	curr = env->phead;
	while (curr)
	{
		if (ft_cmp(curr->key, key))
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
