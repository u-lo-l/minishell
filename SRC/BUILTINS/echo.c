#include "../../INC/minishell.h"
#include <stdlib.h>

void	echo(char *str, char **echo_token)
{
	int	i;

	if (!ft_cmp(str, "echo") || !ft_cmp(echo_token[0], "echo"))
		return ;
	i = 1;
	if (ft_cmp(echo_token[1], "-n"))
		i++;
	while (echo_token[i])
	{
		printf("%s", echo_token[i]);
		i++;
	}
	if (!ft_cmp(echo_token[1], "-n"))
		printf("\n");
}

// int	main()
// {
// 	char *str = "echo";
// 	char **echo_token;

// 	echo_token = malloc(sizeof(char *) * 5);
// 	echo_token[0] = malloc(sizeof(char) * 5);
// 	echo_token[1] = malloc(sizeof(char) * 5);
// 	echo_token[2] = malloc(sizeof(char) * 5);

// 	echo_token[0] = "ech";
// 	echo_token[1] = "-n";
// 	echo_token[2] = "ABC";
// 	echo(str, echo_token);
// }