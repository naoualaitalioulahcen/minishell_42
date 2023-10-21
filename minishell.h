/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nait-ali <nait-ali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 23:37:39 by nait-ali          #+#    #+#             */
/*   Updated: 2023/10/04 20:41:55 by nait-ali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <stdbool.h>
# include <errno.h>

# define DQUOTES 34
# define SQUOTE 39
# define LINE "minishell:$ "

typedef enum e_types
{
	pip,
	word,
	rd_input,
	rd_output,
	rd_output_append,
	heredoc,
	newline
}	t_types;

typedef struct s_subStruct
{
	char				*data;
	int					type;
	int					cls;
	char				*expand;
	struct s_subStruct	*next;
	struct s_subStruct	*prev;
}	t_substruct;

typedef struct s_cmd{
	char			*data;
	int				i;
	pid_t			*pd;
	int				**fds;
	t_substruct		*s_substruct;
	int				filein;
	int				fileout;
	struct s_cmd	*next;
	int				herd;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_environement
{
	char					*env;
	char					*cle;
	char					*valeur;
	struct s_environement	*next;
}	t_environement;

typedef struct s_data
{
	int				exit_status;
	t_environement	*environement;
	int				sqflg;
	int				dqflg;
	int				cmp;
}	t_data;

extern int	g_flag_signal;

typedef struct s_tmp
{
	int		**fds;
	t_cmd	*ls;
}	t_tmp;

typedef struct s_expand{
	int		size;
	int		start;
	char	*str;
	char	*tmp;
	char	*ret;
	char	*ret1;
	char	*value;
}t_expand;

typedef struct s_qvar
{
	char	*result;
	char	*str;
	char	*rest;
	char	*tmp;
	int		type;
}t_qvar;

typedef struct s_varn
{
	char		**option;
	int			**fds;
	pid_t		*pd;
	int			size;
	int			i;
}t_varn;

typedef struct s_check
{
	char	*name_fd;
	int		mode;
	int		permession;
}	t_check;

typedef struct s_export
{
	char	*var;
	int		i;
}	t_export;

void			sigint_herdoc(int sig);
char			**ft_split(char *s, char c);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_get_path(char *argv, char **env);
int				get_ev(char **env);
size_t			ft_strlen(const char *str);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strdup(const char *s);
char			*ft_substr(char *s, unsigned int start, size_t len);
void			print_cmds(t_cmd *ls);
int				syntaxe_error(t_cmd *ls, t_data *nv);
t_cmd			*ft_lstnew(char *cmd, t_data *nv);
int				ft_lstsize(t_cmd *lst);
t_cmd			*ft_lstlast(t_cmd *lst);
void			ft_lstadd_back(t_cmd **lst, t_cmd *new);
int				get_type(char *s);
t_substruct		*n_lstnew(char *cmd);
int				n_lstsize(t_substruct *lst);
t_substruct		*n_lstlast(t_substruct *lst);
void			n_lstadd_back(t_substruct **lst, t_substruct *new);
char			*get_quotes(char *cmd, int *start, int type);
char			*get_redirection(char *cmd, int *start);
char			*get_command(char *cmd, int *start, t_cmd *l, t_data *nv);
char			*ft_strtrim(char *s1, char *set);
void			free_sublist(t_substruct **substruct);
void			free_list(t_cmd **substruct);
void			exec_chile(char **option, char **env, t_cmd *list, t_data *nv);
void			here_doc(char *tmps, char *end, t_data *nv, t_cmd *l);
void			ft_free(char **str);
int				ft_check_fils(t_check *check, t_data *nv, t_cmd *l);
void			ft_execution(t_cmd *list, char **env, t_data *nv);
char			**__resize(char **Array, char *new);
void			ft_close(t_cmd *ls);
void			ft_close_pipe(t_cmd *ls, int **fds);
void			ft_free_matrix(int **str, int size);
int				get_rd(t_substruct **cmd, t_tmp *var, t_data *nv);
int				find_equal_or_plus(char *s, char c);
t_environement	*create_env(char **tab);
void			ft_cd(t_cmd *cmd, char **option, t_data *nv);
void			ft_echo(t_cmd *ls, char **option, t_data *nv);
void			ft_env(t_cmd *cmd, t_data *nv);
void			ft_exit(t_cmd *lst, t_data *nv);
int				ft_strcmp(char *s1, char *s2);
void			ft_putstr_fd(char *s, int fd);
int				ft_atoi(char *str, t_data *nv);
char			*ft_strchr(const char *s, int c);
void			ft_pwd(t_cmd *cmd, t_data *nv);
void			ft_unset(t_cmd *cmd, t_data *nv, char **option);
void			free_environement(t_data *nv);
void			lstadd_back_environement(t_environement **lst, \
t_environement *new);
t_environement	*creation_node_in_env(char *env, char *key, char *val);
void			ft_export(t_cmd *cmd, char **option, t_data *nv);
int				check_builtins(t_cmd *cmd, char **option, \
char **env, t_data *nv);
char			*subc_quots(char *str);
char			*ft_itoa(int n);
void			option_cmd_quots(char **option);
void			init_signals(void);
void			signals_in_child_process(int status, t_data *nv);
char			**get_env_values(t_environement *env_list);
void			init_environement(char **env, t_data *nv);
void			message_error(char *s1, char *s2, char *s3);
void			print_environement(t_cmd *ls, t_data *nv);
int				chedir_error(char *to, t_data *nv);
int				cd_not_exist_directory(char *to, t_data *nv);
void			error_args_export(char *varr);
int				valid_args(char *var);
char			*str_sans_plus(char *str);
void			export_new_var_in_env(char *str, t_export *tmp, \
char c, t_data *nv);
void			message_error(char *s1, char *s2, char *s3);
int				get_cmds(char *line, t_cmd **list, t_data *nv);
int				check_linesps(char *line);
int				check_doll(char *str, char c);
void			ft_free_str(char *str);
int				is_alpha(char c);
void			free_env_values(char **env_values);
void			ft_creat_pipe(int size, int **fds, t_data *nv);
void			ft_free_matrix(int **str, int size);
void			ft_close(t_cmd *ls);
int				help_get_rd3(t_substruct **cmd, t_tmp *var, t_data *nv);
int				help_get_rd2(t_tmp *var, t_substruct **cmd, t_data *nv);
char			*getlastcmd(t_cmd *cmd);
void			help_get_rd(t_substruct **cmd, t_tmp *var, t_data *nv);
char			*get_str1(char *cmd, int *i, t_cmd *l, t_data *nv);
int				help_get_cmds(char *line, t_cmd **list, t_data *nv);
int				check_linesps(char *line);
int				check_doll(char *str, char c);
void			ft_free_str(char *str);
int				is_alpha(char c);
int				ft_size_nam(char *str, char c);
void			free_env_values(char **env_values);
char			*ret_expand_val(char *str, char **env);
void			expand_env_variable(char **option, char **env, t_data *nv);
char			*option_expand(char *line, char **env, t_data *nv);
void			ft_dup(t_cmd *ls, char **option, char **env, t_data *nv);
void			error_str(char *str, t_data *nv);
void			get_option(char ***option, t_substruct *tmps);
int				checkrd(t_cmd *tmp, t_substruct *tmps, int **fds, t_data *nv);
void			wait_pd(t_varn *var, int size, t_data *nv);
char			*get_str2(char *cmd, int *i, t_data *nv, t_cmd *l);
char			*get_inside_quotes(char *cmd, int *i, int type);
char			*get_outside_quotes(char *cmd, int *i);
int				len_wordsplit(char *s, int **j, char c);
void			malloc_wordspl(char **cases, int len, \
int *found_s, int *found_d);
char			*get_redirection(char *cmd, int *start);
int				ft_isalpha(int c);
char			*get_command1(char *cmd, int *start);
int				help_cd(char *to, t_data *nv);
void			change_directories(char *pwd, t_data *nv);
int				help_export(int flag, char *var, char *varr);
int				line_filpip(char *line);
int				non_closed_quotes(char *line);
char			*help_expand(char **env, char *tmp);
char			*ret_expand_val(char *str, char **env);
int				check_if_exitstatus(t_expand *exp, t_data *nv);
void			free_execution(t_varn *var, t_cmd *list);
int				check_first_c(char c);
int				check_first_c2(char c);
#endif
