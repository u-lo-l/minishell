#include "../../../INC/minishell.h"

int	ft_keylen(char *str)	//key 길이 측정
{
	int	i;

	i = 0;
	while (str[i] != '=')	// '=' 전까지
		i++;
	return (i);
}

int	ft_cmp(char *str1, char *str2)	//문자열 같은지 검사하는 함수
{
	int	i;

	i = 0;
	while (str1[i] && str2[i] != '\n')
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	if (str1[i] == '\0' && (str2[i] == '\n' || str2[i] == '\0'))
		return (1);
	return (0);
}