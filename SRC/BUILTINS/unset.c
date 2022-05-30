/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyoo <yyoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:51:51 by yyoo              #+#    #+#             */
/*   Updated: 2022/05/30 18:51:13 by yyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdlib.h>

/* unset할 노드가 head노드 또는 tail 노드 일 때 사용되는 함수*/
void	free_head_tail(t_env *env, t_envnode *target)
{
	if (env->phead == env->ptail)
	{
		free(target);
		env->phead = NULL;
		env->ptail = NULL;
	}
	else if (target == env->phead)
	{
		env->phead = target->nextnode;
		target->nextnode->prevnode = NULL;
		free(target);
	}
	else if (target == env->ptail)
	{
		env->ptail = target->prevnode;
		target->prevnode->nextnode = NULL;
		free(target);
	}
}

/* env_list를 순회하면서 타겟을 찾음 */
void	traversal_env(t_env *env, t_token *curr)
{
	t_envnode	*target;

	target = env->phead;
	while (target)
	{
		if (ft_cmp(target->key, curr->text))
		{
			if (target == env->phead || target == env->ptail)
			{
				free_head_tail(env, target);
				return ;
			}
			target->prevnode->nextnode = target->nextnode;
			target->nextnode->prevnode = target->prevnode;
			free(target);
			return ;
		}
		target = target->nextnode;
	}
}

t_env	*do_unset(t_env *env, t_token_list *unset_token)
{
	t_token	*curr;

	curr = unset_token->head;
	if (!ft_cmp(curr->text, "unset"))
		return (env);
	curr = curr->next;
	while (curr)
	{
		traversal_env(env, curr);
		curr = curr->next;
	}
	return (env);
}

/*
int main(int argc, char **argv, char **envp)
{
	t_env	*ev;
	char	**token;

	(void)argc;
	(void)argv;
	token = malloc(sizeof(char *) * 5);
	token[0] = malloc(sizeof(char) * 6);
	token[1] = malloc(sizeof(char) * 10);
	token[2] = malloc(sizeof(char) * 10);
	token[3] = malloc(sizeof(char) * 10);

	token[0] = "unset";
	token[1] = "HOME";
	token[2] = "LS_COLORS";

	ev = env_list(envp);
	ev = do_unset(ev, token);
	env(ev);
}
*/
