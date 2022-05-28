#include <stdio.h>
#include <stdlib.h>
#include "../INC/minishell.h"

void	copy_element(char *envp, t_envnode *new_node, int len, int keylen)
{
	int			j;
	
	new_node->key = malloc(sizeof(char) * (keylen + 1));
	new_node->value = malloc(sizeof(char) * (len - keylen));
	j = 0;
	while(envp[j] && j < keylen)		// key길이 만큼 copy
	{
		new_node->key[j] = envp[j];
		j++;
	}
	new_node->key[j] = '\0';
	j = 0;
	while (envp[j + keylen] && j < (len - keylen - 1))	// 전체 길이 - key길이 - 1(해주는 이유는 '=' 때문) value copy
	{
		new_node->value[j] = envp[j + keylen + 1];
		j++;
	}
	new_node->value[j] = '\0';
}

void	add_node(char *envp, t_env *env, int i)
{
	t_envnode	*new_node;
	int			len;		// key + '=' + value 길이 
	int			keylen;		// key 길이

	len = ft_strlen(envp);
	keylen = ft_keylen(envp);
	new_node = malloc(sizeof(t_envnode));
	new_node->nextnode = NULL;
	new_node->prevnode = NULL;
	if (i == 0)				// 첫 노드 생성일 때
	{
		env->phead = new_node;	// 헤더 노드 -> new_node;
		env->ptail = new_node;	// 꼬리 노드 -> new_node;
	}
	else					//	두번째 노드 부터는 여기
	{
		new_node->prevnode = env->ptail;
		env->ptail->nextnode = new_node;	// 꼬리 노드의 다음노드 -> new_node
		env->ptail = new_node;				// 꼬리 노드 -> new_node
	}
	copy_element(envp, new_node, len, keylen);	// key ,value를 노드에 저장
}

t_env	*env_list(char **envp)
{
	int		i = 0;
	t_env	*env;	// 환경변수 담을 리스트
	
	env = malloc(sizeof(t_env));
	env->element = 0;
	env->error = 0;
	while (envp[env->element] != NULL)	// 환경변수 개수 체크
		env->element++;

	while (envp[i])		// 환경변수를 env 리스트에 넣는 함수
	{
		add_node(envp[i], env, i);	// 노드를 추가
		i++;
	}
	return (env);
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
		free(curr->key);
		free(curr->value);
		free(curr);
		curr = next;
	}
	free(envlst);
}