/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalliot <aalliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/13 12:45:08 by aalliot           #+#    #+#             */
/*   Updated: 2015/02/13 12:45:10 by aalliot          ###   ########.fr       */
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
# elif __linux
#  include <sys/types.h>
#  include <sys/wait.h>
# endif

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

//typedef struct		s_usetenv
//{
//	t_list			**tmp;
//	t_list			*last;
//	t_list_elem		*elem;
//	t_list			*tmp2;
//	int				i;
//}					t_usetenv;

typedef struct		s_cd
{
	char			*path;
	char			*home;
}					t_cd;

t_list				*get_env(char *envp[]);
char				*get_path(t_list *env, char *bin);
char				**env_to_str(t_list *env);
char				*get_data(t_list *env, char *key);
void				free_path(t_path *path);

int					c_env(t_list *env, char *args[]);
int					c_setenv(t_list *env, char *args[]);
int					c_unsetenv(t_list **env, char *args[]);
int					c_cd(t_list *env, char *args[]);

int					exec(char *bin, char *args[], t_list *env);
void				prompt(t_list *env);
int					command(char *line, t_list **env);

void				print_error(int ind, char *args);
void				ft_exit();

#endif
