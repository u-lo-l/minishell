# include <stdio.h>
# include <stdlib.h>

typedef struct s_envnode
{
	char		*key;
	char		*value;
	struct s_envnode	*nextnode;	// 다음 인덱스의 환경변수
}   t_envnode;

typedef struct s_env
{
	int			element;	// 환경변수 개수
	t_envnode	*phead;	// 헤드노드
	t_envnode	*ptail; // 꼬리노드
}   t_env;

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
	while (str[i] != '=')
		i++;
	return (i);
}

void	cp_element(char *envp, t_env *env, t_envnode *new_node, int len, int keylen)
{
	char		*key;
	char		*value;
	int			j;
	
	key = malloc(sizeof(char) * (keylen + 1));
	value = malloc(sizeof(char) * (len - keylen));
	j = 0;
	while(envp[j] && j < keylen)
	{
		key[j] = envp[j];
		j++;
	}
	key[j] = '\0';
	j = 0;
	while (envp[j + keylen] && j < (len - keylen - 1))
	{
		value[j] = envp[j + keylen + 1];
		j++;
	}
	value[j] = '\0';
	new_node->key = key;
	new_node->value = value;
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
	if (i == 0)
	{
		env->phead = new_node;
		env->ptail = new_node;
	}
	else
	{
		env->ptail->nextnode = new_node;
		env->ptail = new_node;
	}
	cp_element(envp, env, new_node, len, keylen);
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

int main(int argc, char **argv, char **envp)
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
		add_node(envp[i], env, i);
		i++;
	}
	printf("%d\n\n", env->element);
	pisplay_env(env);
}

