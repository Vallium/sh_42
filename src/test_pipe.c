#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

void		run_pipe (void) {
	int const	READ_END = 0;
	int const	WRITE_END = 1;
	pid_t		child = -1;
	int		pdes[2];

	char	*cmd1 = NULL;
	char	*cmd2 = NULL;
	char	*args1[3];
	char	*args2[3];

	cmd1 = "/bin/ls";
	args1[0] = cmd1;
	args1[1] = "-lf";
	args1[2] = NULL;

	cmd2 = "/bin/cat";
	args2[0] = cmd2;
	args2[1] = "-e";
	args2[2] = NULL;

	pipe(pdes);

	child = fork();

	switch ((int)child) {
		case -1:
			close(pdes[READ_END]);
			close(pdes[WRITE_END]);
			perror("error");
		case 0:
			dup2(pdes[WRITE_END], STDOUT_FILENO);
			close(pdes[READ_END]);
			execve(cmd1, args1, NULL);
			perror("error");
			break;
	}

	dup2(pdes[READ_END], STDIN_FILENO);
	close(pdes[WRITE_END]);
	wait(NULL);
	execve(cmd2, args2, NULL);
}

int			main(void) {
	pid_t	child = -1;

	child = fork();

	switch ((int)child) {
		case -1:
			perror("error");
			break;
		case 0:
			run_pipe();
			perror("error");
			break;
	}
	wait(NULL);

	return 0;
}
