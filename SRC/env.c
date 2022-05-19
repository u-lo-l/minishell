#include <stdio.h>

typedef struct s_envnode
{
	char		*key;
	char		*value;
	t_envnode	*nextnode;
}   t_envnode;

typedef struct s_env
{
	int		
	struct  *phead;
}   t_env;

int	ft_cmp(char *av, char *str)
{
	int	i;

	i = 0;
	while (av[i] && str[i] != '\n')
	{
		if (av[i] != str[i])
			return (0);
		i++;
	}
	if (av[i] == '\0' && (str[i] == '\n' || str[i] == '\0'))
		return (1);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	int	i = 0;
	int	j = 0;
	
	if (argc < 2)
	{
		printf("e\n");
		return (0);
	}
	while (envp[i] != NULL)
	{
		printf("%s", envp[i]);
		printf("\n", i);
		i++;
	}
}
