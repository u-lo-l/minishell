/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:45:36 by dkim2             #+#    #+#             */
/*   Updated: 2022/06/13 17:14:27 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/minishell.h"
#include <stdlib.h>
#include <termios.h>

static int	init_shell(int argc, char **argv, struct termios *atr)
{
	struct termios	temp_attr;

	if (argc > 1 || argv[1] != NULL)
		return (return_err("unexpected err : invalid arguments", FALSE));
	if (set_signal_handler() == FALSE)
		return (return_err("unexpected err : signal handler fail", FALSE));
	if (isatty(0) == FALSE)
		return (return_err("unexpected err : is not a tty", FALSE));
	if (tcgetattr(0, atr) == -1)
		return (return_err("unexpected err : cannot get tty attr", FALSE));
	temp_attr = *atr;
	temp_attr.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, TCSANOW, &temp_attr) == -1)
		return (return_err("unexpected err : cannot set tty attr", FALSE));
	return (TRUE);
}

static int	finish_shell(t_env *envlst, struct termios *origin_atr)
{
	if (envlst)
		free_env_list(envlst);
	if (isatty(0) == FALSE)
		return (FALSE);
	tcsetattr(0, TCSANOW, origin_atr);
	return (0);
}

static void	execute(t_env *envlst, t_token_tree *cmd_token_tree)
{
	if (cmd_token_tree == NULL)
		envlst->error = return_err("err : Bad Syntax!", 1);
	else if (cmd_token_tree->num_of_commands != 0)
		execute_command(envlst, cmd_token_tree);
	else
		envlst->error = 0;
	free_token_tree(cmd_token_tree);
}

int	main(int argc, char **argv, char **envp)
{
	t_input			*input;
	t_env			*envlst;
	t_token_tree	*cmd_token_tree;
	struct termios	origin_attr;

	if (init_shell(argc, argv, &origin_attr) == FALSE)
		exit (1);
	envlst = env_list(envp);
	if (envlst == NULL)
		exit (return_err("unexpected error : invalid envp", 1));
	while (1)
	{
		input = read_command("\033[1;3;33mminish >> \033[0m");
		if (input == NULL)
			break ;
		if (input->cmd[0] == 0)
		{
			free_input(input);
			continue ;
		}
		cmd_token_tree = tokenize_and_parsing(input, envlst);
		execute(envlst, cmd_token_tree);
		free_input(input);
	}
	return (finish_shell(envlst, &origin_attr));
}
