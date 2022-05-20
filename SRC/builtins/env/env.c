#include <stdio.h>
#include <stdlib.h>
#include "../../../INC/minishell_datastructure.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_keylen(char *str)	//key 길이 측정
{
	int	i;

	i = 0;
	while (str[i] != '=')	// '=' 전까지
		i++;
	return (i);
}

void	copy_element(char *envp, t_env *env, t_envnode *new_node, int len, int keylen)
{
	char		*key;
	char		*value;
	int			j;
	
	key = malloc(sizeof(char) * (keylen + 1));
	value = malloc(sizeof(char) * (len - keylen));
	j = 0;
	while(envp[j] && j < keylen)		// key길이 만큼 copy
	{
		key[j] = envp[j];
		j++;
	}
	key[j] = '\0';
	j = 0;
	while (envp[j + keylen] && j < (len - keylen - 1))	// 전체 길이 - key길이 - 1(해주는 이유는 '=' 때문) value copy
	{
		value[j] = envp[j + keylen + 1];
		j++;
	}
	value[j] = '\0';
	new_node->key = key;		// key 노드에 저장
	new_node->value = value;	// value 노드에 저장
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
	if (i == 0)				// 첫 노드 생성일 때
	{
		env->phead = new_node;	// 헤더 노드 -> new_node;
		env->ptail = new_node;	// 꼬리 노드 -> new_node;
	}
	else					//	두번째 노드 부터는 여기
	{
		env->ptail->nextnode = new_node;	// 꼬리 노드의 다음노드 -> new_node
		env->ptail = new_node;				// 꼬리 노드 -> new_node
	}
	copy_element(envp, env, new_node, len, keylen);	// key ,value를 노드에 저장
}

void	pisplay_env(t_env *env)
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

void	do_env(int argc, char **argv, char **envp)
{
	int		i = 0;
	int		j = 0;
	t_env	*env;	// 환경변수 담을 리스트
	
	env = malloc(sizeof(t_env));
	env->element = 0;

	while (envp[env->element] != NULL)	// 환경변수 개수 체크
		env->element++;

	while (envp[i])		// 환경변수를 env 리스트에 넣는 함수
	{
		add_node(envp[i], env, i);	// 노드를 추가
		i++;
	}
	pisplay_env(env);
}

// int main(int argc, char **argv, char **envp)
// {
// 	do_env(argc, argv, envp);
// }
