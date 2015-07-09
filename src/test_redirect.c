#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
// # include "libft.h"

void		run_pipe (void) {
	int const	READ_END = 0;
	int const	WRITE_END = 1;
	int			fd_in = 0;
	pid_t		child = -1;
	int			pdes[2];
	// char	*cmd1 = NULL;
	// char	*cmd2 = NULL;
	// char	*cmd3 = NULL;
	char	*args1[3];
	char	*args2[3];
	char	*args3[3];

	// cmd1 = "/bin/ls";
	args1[0] = "/bin/ls";
	args1[1] = "-la";
	args1[2] = NULL;

	// // cmd2 = "/usr/bin/grep";
	// args2[0] = "/usr/bin/grep";
	// args2[1] = "test_pipe.c";
	// args2[2] = NULL;
	//
	// // cmd3 = "/bin/cat";
	// args3[0] = "/bin/cat";
	// args3[1] = "-e";
	// args3[2] = NULL;

	int		file = open("test_redirect", O_RDWR | O_CREAT | O_SHLOCK);						// simple redirect
	// int		file = open("test_redirect", O_RDWR | O_APPEND | O_CREAT | O_SHLOCK);		// append redirect

	if (file == -1) {
		printf("Open error\n");
		exit(0);
	}

	char **tab[4] = {args1, NULL, NULL, NULL};
	char ***ptr = tab;

	while (*ptr) {
		// pipe(pdes);		// create pipe

		child = fork();

		switch ((int)child) {
			case -1:										// if error
				// close();
				close(file);
				perror("error");
			case 0:											// if cmd1
				// printf("run %s\n", cmd1);
				dup2(file, 1);
				if (*(ptr + 1))
					dup2(file, 1);
				// close(pdes[0]);
				// ft_putstr_fd("hello\n", pdes[WRITE_END]);
				execve(*ptr[0], *ptr, NULL);
				perror("error");
				break;
			default:										// if cmd2
				// printf("run %s\n", cmd2);
				wait(NULL);
				// dup2(pdes[READ_END], STDIN_FILENO);
				// close(pdes[1]);
				// execve(cmd2, args2, NULL);
				// fd_in = file;
				ptr++;
				break;
		}

	}
}

int			main(void) {
	// pid_t	child = -1;
	//
	// child = fork();
	//
	// switch ((int)child) {
	// 	case -1:
	// 		perror("error");
	// 		break;
	// 	case 0:
	// 		run_pipe();
	// 		perror("error");
	// 		break;
	// }
	// wait(NULL);
	run_pipe();
	return 0;
}
