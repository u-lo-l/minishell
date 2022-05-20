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
}   t_env;

// int	ft_strlen(char *str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 		i++;
// 	return (i);
// }

void	add_node(char **envp, t_env *env, int i)
{
	t_envnode	*new_node;
	int			len;		// key + '=' + value 길이 
	int			keylen;		// key 길이
	int			j;

	j = 0;
	len = ft_strlen(env[i]);
	keylen = ft_keylen(env[i]);
	new_node = malloc(sizeof(t_envnode));
	if (i == 0)
		env->phead = new_node;
	else
	{
		
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
		add_node(envp, env, i);
	}
	printf("%d", env->element);

}
