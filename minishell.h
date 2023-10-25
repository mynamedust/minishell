/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeliky <almeliky@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:27:54 by agladkov          #+#    #+#             */
/*   Updated: 2023/07/20 15:44:02 by agladkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <pthread.h>
# include <signal.h>
# include <errno.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

// global variable
extern int	g_exit_status;

//Types
typedef struct s_mlist
{
	struct s_mlist	*next;
	struct s_mlist	*prev;
	int				fd[2];
	int				isheredoc;
	int				heredoc[2];
	int				isoutput;
	int				isinput;
	char			*bin;
	char			**argv;
	char			*command;
}	t_mlist;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	struct s_mlist	**list;
	struct s_env	*env;
}	t_shell;

// len_utils
int		ft_len_spaces(char *str);
int		ft_len_word(char *str);
int		ft_len_quote(char *str, char quote);
int		ft_len_separator(char *str);
int		ft_len_command(char *str);

// argc argv
int		ft_argc(char **arr);
char	**ft_argv(char **arr);

// command
int		ft_amount_commands(char *str);
char	*ft_get_command_from_path(char *command);
char	*ft_get_command_path(char *command);

// env
char	*ft_get_env_value(t_shell *shell, char *var);
char	*ft_get_env_value_by_name(t_shell *shell, char *str);
char	**ft_env_to_arr(t_env *env, int len, int i);
int		ft_env(t_env *env);

// len construction
int		ft_amount_constructions(char *str);
int		ft_len_construction(char *str);

// path
char	*ft_get_absolute_path(t_shell *shell, char *command);

// path utils
char	*ft_pathjoin(const char *path1, const char *path2);
char	*ft_find_path(t_shell *shell, char *command);
char	*ft_check_file_in_current_directory(t_shell *shell, char *filename);

// construction
int		ft_count_construction(char *str);
char	**ft_parse_construction(t_shell *shell, char *str);
char	*ft_set_env(t_shell *shell, char *str);

// construction utils
int		ft_num_quotes(char *str);
char	*ft_delete_quotes(char *str);
void	ft_change_element_with_free(t_shell *shell, char **out, int n);

// parse utils
int		ft_len_before_quote(char *str);
char	*ft_parse_quotes(t_shell *shell, char *str);
int		ft_len_env_key(char *str);

// free
void	ft_free_2d_array_with_null(char **array);
void	ft_list_clear(t_mlist **list);
void	ft_free_2_linked_list(t_mlist **list);

// list utils
t_mlist	*ft_list_new(t_shell *shell, char **argv, char *command);
t_mlist	*ft_list_last(t_mlist *list);
void	ft_list_add_front(t_mlist **list, t_mlist *new);
void	ft_list_add_back(t_mlist **list, t_mlist *new);
void	ft_list_clear(t_mlist **list);

// fill list
int		ft_len_nullable_2d_array(char **arr);
t_mlist	*ft_fill_list(t_shell *shell, char *str);

// pipex
void	ft_pipex(t_mlist *list);

// action
void	ft_action(int sig);
void	ft_quit(int sig);
void	ctrl_d_handler(char *str);
void	ft_sigint(int signum);
void	ft_sigquit(int sig);

// init actions
void	ft_init_action(void);
void	ft_define_signals(void);

//minishell_create_envlist
t_env	*ft_env_add(char *str);
t_env	*ft_create_envlist(char	**arr);

//minishell_cd
int		ft_cd(char	**args, t_env **env, char *arr, int status);
void	ft_cd_err(char **args, int *status);
int		ft_cd_key(char	**args, t_env **env, char *str);
void	ft_cd_change(char *arg, t_env **env);

//minishell_export
int		ft_export(char **args, t_env **env);
void	ft_export_change(t_env *env, char *str);
int		ft_find_env(char *str, t_env *env);
t_env	*ft_ptr_by_key(char *key, t_env *env);
char	*ft_value_by_key(char *key, t_env *env);

//minishell_export_utils
int		ft_export_print(t_env *env);
void	ft_export_add(char *str, t_env **env);
void	ft_export_errprint(char *arg);
int		ft_export_valid(char *arg, int *res, t_env *env);

//minishell_unset
int		ft_unset(char **args, t_env **env, int status);
int		ft_strcmp(char *s1, char *s2);
int		ft_unset_valid(char *arg);
void	ft_unset_errprint(char *arg);
void	ft_node_del(t_env **node);

//minishell_pwd
int		ft_pwd(void);

//minishell_echo
int		ft_echo(char **args, int n);

//minishell_exit
int		ft_exit(char **args);
int		ft_num_check(char *arg);

// redirect error
int		ft_redirect_unexpected_error(char *command);
int		ft_redirect_error_argument(t_mlist *list, int n);

// redirect input
int		ft_check_one_redirect_input_argument(t_mlist *list, int n);
int		ft_one_redirect_input(t_mlist *list, int n);
int		ft_check_next_redirect_input_argument(t_mlist *list, int n);
int		ft_two_redirect_input(t_shell *shell, t_mlist *list, int n);
int		ft_redirect_input(t_shell *shell, t_mlist *list, int n);

// redirect utils
void	ft_remove_redirect(char ***argv, int n);
void	ft_dup_redirect(t_mlist *list);
int		ft_check_one_redirect_input_argument_utils(t_mlist *list, int n, \
		struct dirent *f, DIR *d);

// redirect
int		ft_handle_redirect(t_shell *shell, t_mlist *list);

// redirect output
int		ft_redirect_two_output(t_mlist *list, int n);
int		ft_redirect_one_output(t_mlist *list, int n);
int		ft_redirect_output(t_mlist *list, int n);

void	ft_close_pipe(int fd[2]);

// minishell builtin utils
int		ft_isbuiltin(char *path);
int		ft_check_n_flag(char **arr);
int		ft_builtin_bin(t_shell *shell, t_mlist *list, int command);
int		ft_builtin_executor(t_shell *shell, t_mlist *list, int command);
int		ft_builtin_handler(t_shell *shell, t_mlist *list);
char	*ft_lowercase(char *str);
char	**ft_echo_skip_flags(char **arr);
t_env	*ft_del_first(t_env **node);

// minishell pipe utils
void	ft_close_pipe(int fd[2]);
void	ft_dup_pipe(t_mlist *list);
void	ft_close_fd(t_mlist *list);

// minishell executor
int		ft_executor(t_shell *shell, t_mlist *list);

// main
int		ft_print_error(t_mlist *list);
void	executor(t_shell *shell);

// utils
void	ft_delete_qoute_in_argv(char **argv);
int		ft_is_valid_linked_list(t_mlist *list);
int		ft_check_redirect_error(t_mlist *list, int n);
int		ft_is_valid_argv(t_mlist *list);
int		ft_check_pipe_error(t_mlist *list);

// parser
t_mlist	*ft_parser(t_shell *shell, char *str);
char	**ft_tokenizer(char *str);

// tokenizer utils
int		ft_len_token(char *str);
int		ft_is_separator(char *str);
int		ft_token_count(char *str);
void	ft_split_token(char **tokens, char *str);

// constructor
t_mlist	*ft_constructor(t_shell *shell, char **tokens);

// constructor utils
t_mlist	*ft_create_list(t_shell *shell, char **tokens);
t_mlist	*ft_create_list_node(t_shell *shell, char **tokens);
int		ft_token_count_in_construction(char **tokens);
char	*ft_find_token(char **tokens, char *token);
void	ft_set_env_token(t_shell *shell, char **tokens);
char	**ft_slice_arr(char **arr, int start, int end);
int		ft_length_construction(char **tokens);
int		ft_len_between_quotes(char *str);

// test
void	ft_validator_test_run(t_shell *shell);
void	ft_executor_test_run(t_shell *shell);

#endif
