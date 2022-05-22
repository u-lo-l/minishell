<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:32:33 by dkim2             #+#    #+#             */
/*   Updated: 2022/05/22 18:32:34 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

=======
>>>>>>> 482b848a2cb3ea3acef8068f9c541b6ca1cd5229
#include "../../INC/minishell.h"
#include <stdio.h>
#include <stdlib.h>

<<<<<<< HEAD
char	*word_expansion(t_input	*input, t_env *env_list)
{
	char	*key;
	char	*value;

	key = NULL;
	while (ft_isalnum(input->cmd[input->curr_i]) || \
			input->cmd[input->curr_i] == '_')
		input->curr_i++;
	input->curr_i--;
	make_word(input, &key);
	input->start_i = ++input->curr_i;
	if (key == NULL)
		return (NULL);
	value = search_key(env_list, key);
	free(key);
	return (value);
}
/*
int main(int argc, char **argv, char **envp)
{
	t_env	*env;
	char	*val;

	if (argc != 1 || argv == NULL || envp == NULL)
		return (1);
	env = env_list(envp);
	if (env == NULL)
		return (1);
	// display_env(env);
	// val = word_expansion(env, "PATH");
	val = search_key(env, "SHELL");
	printf("<%s>\n", val);
	return (0);
}*/
=======
static int	ft_keylen(char *str)	//key 길이 측정
{
	int	i;

	i = 0;
	while (str[i] != '=')	// '=' 전까지
		i++;
	return (i);
}

static void	copy_element(char *envp, t_envnode *new_node, int len, int keylen)
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

static void	add_node(char *envp, t_env *env, int i)
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
	copy_element(envp, new_node, len, keylen);	// key ,value를 노드에 저장
}

static void	display_env(t_env *env)
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

static t_env	*make_env_list(char **envp)
{
	int		i;
	t_env	*env;
	
	env = malloc(sizeof(t_env));
	env->element = 0;
	while (envp[env->element] != NULL)
		env->element++;
	i = -1;
	while (envp[++i])
		add_node(envp[i], env, i);
	return (env);
}


static char *get_env_value(t_env *env_list, const char *key)
{
	t_envnode	*curr_node;
	char		*value;

	if (env_list == NULL || key == NULL)
		return (NULL);
	curr_node = env_list->phead;
	while (curr_node != NULL);
	{
		if (ft_strncmp(curr_node->key, key, ft_strlen(key)) == 0)
		{
			value = curr_node->value;
			return (value);
		}
		curr_node = curr_node->nextnode;
	}
	return (NULL);
}

char	*word_expansion(t_input	*input, t_env	*env_list)
{
	while (TRUE)
	{
		if (input->cmd[input->curr_i] == ' ' \
			input->cmd[input->curr_i] == '\t' \
			input->cmd[input->curr_i] == '\0')
		
	}
}

int main(int argc, char **argv, char **envp)
{
	t_env	*env_list;

	if (argc != 1 || argv == NULL || envp == NULL)
		return (1);
	env_list = make_env_list(envp);
	if (env_list == NULL)
		return (1);
	// display_env(env_list);
}
>>>>>>> 482b848a2cb3ea3acef8068f9c541b6ca1cd5229
