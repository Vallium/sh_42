/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 12:45:08 by adoussau          #+#    #+#             */
/*   Updated: 2015/02/13 12:45:10 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_1_H
# define SH_1_H

# include "libft.h"
# include "get_next_line.h"
# include <unistd.h>
# include <sys/stat.h>

# ifdef __APPLE__
#  include <sys/types.h>
#  define GET_CWD getwd(0);

# elif __linux__
#  include <sys/types.h>
#  include <sys/wait.h>
#  include <unistd.h>
#  define GET_CWD get_current_dir_name()

# endif

typedef struct		s_cmd
{
	char			*bin;
	char			**args;
}					t_cmd;

typedef struct		s_list_elem
{
	char			*key;
	char			*data;
}					t_list_elem;

typedef struct		s_path
{
	char			*path;
	char			**paths;
	char			**tmp;
	char			buff[1024];
	char			*ret;
	struct stat		stat_buff;
}					t_path;

typedef struct		s_setenv
{
	t_list			*tmp;
	t_list_elem		*elem;
	t_list_elem		new;
}					t_setenv;

typedef struct		s_usenv
{
	t_list			*current;
	t_list			*prev;
	t_list			*to_delete;
	t_list_elem		*to_del;
}					t_usenv;

typedef struct		s_cd
{
	char			*path;
	char			*home;
	t_list_elem		*pwd;
	t_list_elem		*old;
	t_list_elem		elem;
}					t_cd;

typedef struct		s_command
{
	char			*bin;
	char			**args;
}					t_command;

void				ft_exit(char **args, int msg);

t_list				*get_env(char *envp[]);
char				*get_path(t_list *env, char *bin);
char				**env_to_str(t_list *env);
char				*get_data(t_list *env, char *key);

int					command_free(char *args[], char *line, char *bin);
int					free_home_path(t_list *env, t_cd *cd);
void				free_path(t_path *path);
int					magic_free(void *ptr);

int					c_env(t_list *env, char *args[]);
int					c_setenv(t_list **env, char *args[]);
int					c_unsetenv(t_list **env, char *args[]);
int					c_cd(t_list *env, char *args[]);

int					exec(char *bin, char *args[], t_list *env);
void				prompt(t_list *env);
int					command(char *line, t_list **env);

int					print_error(int ind, char *args);
void				ft_exit(char **args, int msg);

t_list_elem			*get_elem(t_list *env, char *key);

#endif
