#ifndef ENV_H
# define ENV_H

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
    t_envnode   *ptail;
}   t_env;

#endif