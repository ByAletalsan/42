/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atalaver <atalaver@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:43:49 by dvasco-m          #+#    #+#             */
/*   Updated: 2023/06/28 18:29:53 by atalaver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "shell_utils.h"
# include <dirent.h>
# include <sys/types.h>

# define T_LEAF 0
# define T_OR 1
# define T_AND 2
# define T_ERROR 3

# define CODE_ERROR 1

typedef struct s_cmdtree {
	int					type;
	int					rc;
	struct s_cmdtree	*left;
	struct s_cmdtree	*right;
	char				*cmd;
}	t_cmdtree;

typedef struct ficheros
{
	int		fi;
	int		ft;
	char	*f_word;
	int		fs;
	int		control_i;
}	t_ficheros;

typedef struct varbox
{
	char		path[1024];
	t_list		*enviroment;
	int			exit_code;
	int			exit;
	int			flag_c;
	char		*header;
}	t_varbox;

typedef struct ejevars
{
	t_ficheros	tp;
	pid_t		pid;
	char		*route;
	int			status;
	int			i;
	int			j;
	int			npipes;
	int			control_route;
	int			builtin;
	char		**cmd_opt;
	char		**inpipes;
	int			**pipes;
}	t_ejevars;

typedef struct iwc
{
	int		nwc;
	int		wci;
	int		wcf;
	char	**ptrn;
	char	*p;
	int		r;
	char	path[1024];
}	t_iwc;

t_cmdtree	*ft_build_cmdtree(char *cmd);
void		ft_exec_cmdtree(t_cmdtree *tree);
void		ft_free_cmdtree(t_cmdtree *tree);
char		*export_value(char *var);
char		*expand_envar(char *line);
int			ejecutor_i(char *ins, int code);
int			actualizar_exit_code(int code);
char		*clean_spaces(char *str);
char		*strdeleted(char *s, int p1, int p2);
char		*search_name(char *cmd, int len);
int			salida(char *cmd, t_ficheros *tp, int type);
int			entrada(char *cmd, t_ficheros *tp, int type, char *name);
char		*open_and_format(char *s, t_ficheros *tp, int i, char *cmd);
void		ft_freedom(char **inpipes, char **cmd_opt, int **pipes,
				char *route);
int			**creat_pipes(int npipes);
int			count_pipes(char **inpipes);
char		*find_path(char *cmd, int *control, int i);
int			procrear(t_ejevars *v, char **inpipes, int **pipes, char **cmd_opt);
t_list		*find_node_enviro_with_key(char *key, t_list *list);
t_list		*wildcard_gestor(char *str);
char		*search_wc(int i, int j, char *line, int *q);
char		*insert_list(char *line, t_list *list, int j, int *i);
char		*insert_content(char *res, t_list *list, int *len);
void		aumentar_profundidad(t_list *list, int shlvl, char *aux2,
				char *aux3);
int			size_name(char *cmd, char *name, int type, int len);
int			is_builtin(char **cmd_opt);
int			ft_exec_builtin(t_ejevars *v, char **cmd_opt);
int			builtin(t_ejevars *v, int **pipes, char **cmd_opt);
char		**env_to_matrix(t_list *list, int i);
char		*ft_clean_bars(char *path, int i, char *aux_join, char *aux);
int			ft_check_var_name(char *s);
int			ft_no_valid_name(void);
void		read_buffer(t_ficheros *tp, char *end);
int			ft_lim_bash(char c);
int			check_sintax(char *s, char c, int i);

//BUILTINS
int			ft_pwd(char **cmd_opt);
int			ft_exit(char **cmd_opt, char *aux);
int			ft_env(char **cmd_opt);
int			ft_export(char **cmd_opt, char **split);
int			ft_unset(char **cmd_opt);
int			ft_echo(char **cmd_opt);
int			ft_cd(char **cmd_opt);
#endif
