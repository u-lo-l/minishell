#include "../../INC/minishell.h"

t_token_list *scan_token(t_input *input, t_env *env_list)
{
	t_token_list	*toklst;
	t_token			*token;

	toklst = create_empty_toklst();
	while (TRUE)
	{

		if (input->cmd[input->curr_i] == 0)
		{
			token = create_token();
		}
	}
	return (toklst);
}

int main(int argc, char **argv, char **envp)
{
	t_input 		*input;
	t_env			*env_list;
	t_token_list	*cmd_token_list;

	if (argc != 1 || argv == NULL || envp == NULL)
		return (0);
	env_list = make_env_list(envp);
	while (1)
	{
		// 명령어 한 줄 읽어오기
		input = read_command("mini >>  ");
		cmd_token_list = scan_token(input, env_list);
		
		// 읽어 온 명령어를 파싱하여 token_list를 생성한다.
		// (우선은 리스트로 구현하고 개념이 이해되면 트리로 할 계획이다.)
		
		// 파싱 된 명령어를 실행한다.

		free(input->cmd);
		free(input);
	}
	return (0);
