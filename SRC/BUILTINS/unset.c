#include "../../INC/minishell.h"
#include <stdlib.h>

void	free_head_tail(t_env *env, t_envnode *target)
{
	if (env->phead == env->ptail) // 첫노드를 지우는데 노드 개수가 한개 일 때
	{
		free(target);
		env->phead = NULL;
		env->ptail = NULL;
	}
	else if (target == env->phead) // 지울 노드가 헤드 노드일 때
	{
		env->phead = target->nextnode; // 헤드 노드 -> 타겟노드의 다음노드
		target->nextnode->prevnode = NULL; // 다음 노드의 이전포인터-> NULL
		free(target);
	}
	else if (target == env->ptail) // 지울 노드가 꼬리 노드일 때
	{
		env->ptail = target->prevnode; // 꼬리 노드 -> 타겟노드의 이전 노드
		target->prevnode->nextnode = NULL; // 이전 노드의 다음포인터 -> NULL
		free(target);
	}
}

t_env	*do_unset(t_env *env, char *key)
{
	t_envnode	*target;

	target = env->phead;
	while (target)	// 순회
	{
		if (ft_cmp(target->key, key))	// 입력한 키값과 같은 키의 노드가있을 때
		{
			if (target == env->phead || target == env->ptail) // 지울 노드가 머리 or 꼬리 노드일 때
			{
				free_head_tail(env, target);
				return (env);
			}
			target->prevnode->nextnode = target->nextnode; // 이전 노드의 다음노드 포인터값->타겟노드의 다음 노드
			target->nextnode->prevnode = target->prevnode; // 다음 노드의 이전노드 포인터값->타겟노드의 이전 노드
			free(target);
			return (env);
		}
		target = target->nextnode;
	}
	return (env);
}

// int main(int argc, char **argv, char **envp)
// {
// 	t_env *env;

// 	env = env_list(envp);
// 	env = do_unset(env, "HOME");
// 	env = do_unset(env, "COLORTERM");
// 	env = do_unset(env, "LS_COLORS");
// 	env = do_unset(env, "PATH");
// 	env = do_unset(env, "SHELL");
// 	env = do_unset(env, "TERM_PROGRAM_VERSION");
// 	env = do_unset(env, "_");
// 	env = do_unset(env, "WSL_DISTRO_NAME");
// 	env = do_unset(env, "VSCODE_IPC_HOOK_CLI");
// 	env = do_unset(env, "TERM_PROGRAM");
// 	env = do_unset(env, "PATH");
// 	display_env(env);
// }