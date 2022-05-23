/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyoo <yyoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 13:51:44 by yyoo              #+#    #+#             */
/*   Updated: 2022/05/23 13:51:46 by yyoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INC/minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	do_pwd(void)
{
	char	*buff;

	buff = malloc(sizeof(char) * 1024);
	getcwd(buff, 1024);
	printf("%s\n", buff);
	free(buff);
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
