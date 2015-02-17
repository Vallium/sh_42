#include "sh_1.h"

//int		line_trim(char **line)

int		command(char *line, t_list *env)
{
	char	*bin;
	char	**args;

	line = ft_strtrim(line);
	if (!line || !line[0])
		return (0);
	args = ft_strsplit(line, ' ');
	if (!args || !args[0] || !args[0][0])
		return (0);
	bin = get_path(env, args[0]);
	if (!ft_strcmp(args[0], "exit"))
		ft_exit();
	else if (!ft_strcmp(args[0], "cd"))
		return (c_cd(env, args));
	else if (!ft_strcmp(args[0], "env") || (!ft_strcmp(args[0], "setenv") && !args[1]))
		return (c_env(env, args));
	else if (ft_strcmp(args[0], "unsetenv") == 0)
		return (c_unsetenv(&env, args));
	else if (ft_strcmp(args[0], "setenv") == 0)
		return (c_setenv(env, args));
	else if (bin == (char*)1)
		print_error(1, args[0]);
	else if (bin == NULL || exec(bin, args, env) == -1)
		print_error(2, args[0]);
	return (0);
}

int		exec(char *bin, char *args[], t_list *env)
{
	pid_t	father;
	char	**strenv;

	if (!ft_strchr(bin, '/'))
		return (-1);
	father = fork();
	if (father > 0)
		waitpid(father, NULL, 0);
	if (!father)
	{
		signal(SIGINT, SIG_DFL);
		strenv = env_to_str(env); /*ho putin con, ca fuit fada!!*/
		execve(bin, args, strenv);
		while (*strenv)
			free(*strenv++);
		free(strenv);
	}
	return (1);
}

void	ft_exit()
{
	ft_putendl("exit");
	exit(2);
}

void	print_error(int ind, char *args)
{
	if (ind == 1)
	{
		ft_putstr_fd(args, 2);
		ft_putendl_fd(": Permission denied.", 2);
	}
	else if (ind == 2)
	{
		ft_putstr_fd(args, 2);
		ft_putendl_fd(": Command not found.", 2);
	}
	else if (ind == 3)
	{
		ft_putstr_fd("cd: no such file or directory: ", 2);
		ft_putendl_fd(args, 2);
	}
}

