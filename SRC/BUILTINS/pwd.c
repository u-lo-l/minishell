#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char	*do_pwd(void)
{
	char *buff;

	buff = malloc(sizeof(char) * 1024);
	getcwd(buff, 1024);
	printf("%s\n", buff);
	return (buff);
}

// int main()
// {
// 	char *buff;

// 	buff = do_pwd();
// 	printf("\n");
// 	int i = 0;
// 	while (i < 70)
// 	{
// 		printf("%c", buff[i]);
// 		i++;
// 	}
// 	printf("\n");
// }