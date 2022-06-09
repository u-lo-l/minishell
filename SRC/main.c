/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkim2 <dkim2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 18:45:36 by dkim2             #+#    #+#             */
/*   Updated: 2022/06/09 21:05:03 by dkim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../INC/minishell.h"
#include <stdlib.h>
#include <termios.h>

static int	init_shell(int argc, char **argv, struct termios *atr)
{
	struct termios	temp_attr;

	if (argc > 1 || argv[1] != NULL)
		return (FALSE);
	if (set_signal_handler() == FALSE)
		return (FALSE);
	if (isatty(0) == FALSE)
		return (FALSE);
	if (tcgetattr(0, atr) == -1)
		return (FALSE);
	temp_attr = *atr;
	temp_attr.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, TCSANOW, &temp_attr) == -1)
		return (FALSE);
	ft_putstr_fd("\033[35mminishell start\033[0m\n", 2);
	return (TRUE);
}

static int	finish_shell(t_env *envlst, struct termios *origin_atr)
{
	if (envlst)
		free_env_list(envlst);
	if (isatty(0) == FALSE)
		return (FALSE);
	tcsetattr(0, TCSANOW, origin_atr);
	ft_putstr_fd("\033[35mminishell end\033[0m\n", 2);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_input			*input;
	t_env			*envlst;
	t_token_tree	*cmd_token_tree;
	struct termios	origin_attr;

	if (init_shell(argc, argv, &origin_attr) == FALSE)
		exit (return_err("unexpected error : init fail", 1));
	envlst = env_list(envp);
	if (envlst == NULL)
		exit (return_err("unexpected error : env fail", 1));
	while (1)
	{
		input = read_command("mini >> ");
		if (input == NULL)
			break ;
		cmd_token_tree = tokenize_and_parsing(input, envlst);
		free(input->cmd);
		free(input);
		if (cmd_token_tree == NULL)
			envlst->error = return_err("err : Bad Syntax!", 1);
		else if (cmd_token_tree->num_of_commands != 0)
			execute_command(envlst, cmd_token_tree);
		free_token_tree(cmd_token_tree);
	}
	return (finish_shell(envlst, &origin_attr));
}
