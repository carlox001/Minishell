/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfiorini <sfiorini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:23:11 by sfiorini          #+#    #+#             */
/*   Updated: 2025/05/25 12:13:14 by sfiorini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <ctype.h>
# include <stdint.h>
# include <fcntl.h>
# include <stdarg.h>
# include <limits.h>
# include "utils/utils.h"
# include <wait.h>
# include <signal.h>
# include "globals/global.h"
# include <limits.h>

typedef struct s_program
{
	// prgorgam
	int				exit_code;
	int				id_to_wait;
	int				check_pipe_ex_co;
	int				real_output;
	char			**env;
	char			**cpy_exp;
	unsigned char	*status;
	char			**mtx_line;
	char			*curr_dir;
	char			*pwd;
	char			*home_path;
	char			*old_pwd;
	char			*path;
	// utils
	int				i;
	int				j;
	int				k;
	int				*z;
	int				i_p;
	int				check;
	int				check_hd;
	int				num_hd;
	int				words;
	int				len;
	int				flag;
	int				nflag;
	int				equal;
	int				output;
	int				input;
	int				fd[2];
	int				flag_builtin;
	int				num_cmd;
	int				*in;
	int				*out;
	char			*tmp;
	char			*path_expansion;
	char			*sub_str;
	int				fork_id;
	char			**dup_mtx;
	int				num_fd;
	int				flag_in_operator;
	int				flag_cmd_not_found;
	int				flag_quotes;
	int				expansion_flag;
	int				expansion_hd_flag;
}	t_program;

//	commands
	//	builtin_commands
	//	cd
		//	ft_cd_utils_1.c
void		env_refresh_dir(t_program *shell);
void		refresh_directory(char *path, t_program *shell, int flag);
char		*format_str(char *old_str);
int			only_backslash(char *str);
int			count_backs(char *str, t_program *shell);
		//	ft_cd_utils_2.c
void		cd_no_char(char *str, t_program *shell);
int			no_char(char *str);
void		only_cd(t_program *shell);
void		cd_root(t_program *shell);
char		*cd_back(t_program *shell);
		//	ft_cd_utils_3.c
int			cd_absolute_path(char *str, t_program *shell);
int			cd_relative_path(char *str, t_program *shell);
int			relative_path_core(char *str, int *i, t_program *shell, char *sv);
int			relative_back_slash(char *str, t_program *shell, int i, int j);
void		end_relative_cd(t_program *shell, char *path);
		//	ft_cd_utils_4.c
void		print_too_many_arg(t_program *shell);
		//	ft_cd.c
void		ft_cd(t_program *shell);
void		cd_oldpwd(t_program *shell);
int			cd_checks(t_program *shell);
void		print_cd_error(char *str);
void		relative_error(t_program *shell);
//	echo
		//	ft_echo_utils.c
char		*remove_external_quotes(char *old_str, char q);
char		*remove_external_quotes_core(char \
*old_str, int c_l, int c_r, int i);
int			count_args(char **mtx, int i);
void		check_nflag(char **mtx, t_program *shell);
int			check_dollar(char *str);
		//	ft_echo_utils_2.c
int			get_printable_echo_str(char **str2, t_program *shell);
int			counter_quotes(char *old_str, char q);
void		rem_quote_case(char *old_str, int *i, char **new_str, char q);
void		rem_null_char(char *old_str, int *i, char **new_str);
char		*remove_couple_quotes(char *old_str);
		//	ft_echo_utils_3.c
void		update_counter_and_i(int *i, int *counter);
int			only_quotes(char *str, int *flag);
void		alloc_only_quote(char **sub_str, int flag);
void		echo_if(t_program *shell, char **str2, int *i, int len);
		//	ft_echo.c
void		ft_echo(t_program *shell);
void		ft_echo_core(t_program *shell, char *str2, int *i, int len);
void		ft_echo_core_2(char *str2, int *i, t_program *shell, int len);
	//	export
		//	ft_export_utils_1.c
int			is_there_in_env(t_program *shell, int len, char *str, int *flag);
int			replace(t_program *shell, int len, char *dup);
char		*remove_plus(char *old_str);
void		change_export_value(t_program *shell, int i, int value, char *str);
int			realloc_env(t_program *shell, char *str);
		//	ft_export_utils_2.c
int			only_export(t_program *shell);
int			export_parsing(t_program *shell, int j);
int			export_parsing_2(t_program *shell, char *str);
int			export_parsing_quote(char *str);
		//	ft_export_utils_3.c
char		**order_env(t_program *shell);
void		print_export_error(char *str);
int			there_is_a_plus(char *str);
void		update_plus(char **str);
		//	ft_export.c
void		ft_export(t_program *shell);
int			export_cicle(char *str);
int			exist_in_env(char *str, t_program *shell);
void		print_export_env(t_program *shell, int i, int j);
void		export_core(t_program *shell, int value, int i, char *str);	
	//	unset
		//	ft_unset_utils_2.c
void		print_unset_error(char *str);
int			unset_parsing(t_program *shell, int j);
int			unset_parsing_2(t_program *shell, char *str);
int			unset_parsing_quote(char *str);
		//	ft_unset_utils.c
char		*search_unset(t_program *shell, int l);
void		arg_treatment(t_program *shell, char *arg, int k, int j);
char		*split_dollar(char *old_str, t_program *shell);
void		first_split_dollar_loop(char **mtx, t_program *shell, int flag);
void		second_split_dollar_loop(char **new_str, char **mtx);
		//	ft_unset.c
void		ft_unset(t_program *shell);
char		*search_env_and_allocate(char *env_str, t_program *shell);
char		*expansion_variable(char *old_str, t_program *shell);
void		expansion_variable_end(char **new_str, char *add_str);
	//	other_builtin_2.c
int			ft_pwd(t_program *shell);
int			ft_env(t_program *shell);
	//	other_builtin.c
void		numeric_argument(t_program *shell, char ***mtx_hub);
int			is_there_an_equal(char *str);
void		ft_exit(t_program *shell, char ***mtx_hub);
int			exit_core(t_program *shell, char ***mtx_hub);
void		is_valid_exit(t_program *shell, int *i, char ***mtx_hub);
	//	non_builtin_commands
		//	fork.c
int			child(t_program *shell, int i, int pipe_cmd, char ***mtx_hub);
int			open_files_in_child(t_program *shell, int i, char ***mtx_hub);
void		redirect_in_out_child(t_program *shell, int pipe_cmd, char *path);
void		father(t_program *shell, int j);
void		failed_child(t_program *shell, char ***mtx_hub);
		//	fork_2.c
void		print_error_cringe(char *str);
void		close_child(int flag, t_program *shell, char ****mtx_hub);
void		correct_exit(int code);
void		if_redirect(t_program *shell, char **path);
	//	commands_hub.c
int			check_commands(char *cmd, t_program *shell, int k, char ***mtx_hub);
int			check_builtin(char *cmd, t_program *shell, char ***mtx_hub);
int			exec_non_builtin(t_program *shell, int index, char ***mtx_hub);
void		failed_execve(char **full_cmd, t_program *shell, char ***mtx_hub);
void		clear_non_builtin(t_program *shell, char ***mtx_hub, \
char ***full_cmd);
	//	exec_utils_4.c
void		flag_cmds(t_program *shell, int *flag, int i, char **tmp);
void		skip_quote_cmd(char **tmp, int *i);
int			count_commands(t_program *shell);
	//	exec_utils_3.c
int			ambiguous_redirect(t_program *shell);
void		update_exit_status(t_program *shell);
void		waiting(t_program *shell);
void		else_father(t_program *shell, int *i, int *j, char ***mtx_hub);
int			exec_more_commands(t_program *shell, int j, int i, char ***mtx_hub);
	//	exec_utils_2.c
void		increments(int *i, int *j);
void		set_exec_signals(void);
void		update_counter_exec(int *j, int *i);
void		free_matrix_pointer(char ***mtx_hub);
char		**alloc_builtin_mtx(t_program *shell);
	//	exec_utils.c
int			count_commands2(t_program *shell);
char		***alloc_mtx(int num_commands, t_program *shell);
int			alloc_mtx_core_while(t_program *shell, int \
*i, int *j, char ***mtx_hub);
void		alloc_mtx_core(t_program *shell, char ***mtx_hub);
int			count_commands(t_program *shell);
int			check_flag_builtin(char **mtx, int i);
	//	exec.c
int			exec(t_program *shell);
int			set_exec(t_program *shell, char ****mtx_hub);
int			exec_core(t_program *shell, int j, int num_cmd, char ***mtx_hub);
int			exec_one_command(t_program *shell, int i, char ***mtx_hub);
int			exec_more_commands(t_program *shell, int j, int i, char ***mtx_hub);
	//	get_path_commands.c
char		*getpath(char **envp);
char		*path_find(char **envp, char *command);
char		**get_full_cmd(t_program *shell);
void		path_clear(char *path, char *path_joined, int *i);
int			is_builtin(char *cmd);
	//	get_path_commands_utils.c
int			if_access(char *path, int flag);
//	globals
	//	globals.c
//	other_utils
	//	close.c
void		close_in_out(int *fd, int k, int flag);
void		close_fds(int *fd, int flag, int input);
void		close_all_files(int *fd, int output, int input);
	//	matrix_utils.c
void		print_matrix(char **matrix);
int			matrix_len(char **matrix);
void		free_matrix(char **matrix);
void		free_matrix_len(char **matrix, int len);
char		**matrix_dup(char **old_mtx);
	//	signals.c
void		sig_handler_child(int sig);
void		sig_handler(int sig);
void		sig_handler_hd(int sig);
//	parsing
	//	count_words.c
int			count_words(char *str, t_program *shell);
void		skip_quote(t_program *shell, char *str, char q);
void		continue_count(t_program *shell, char *str, int *flag, int *words);
void		operator_count(t_program *shell, char *str, int *words);
int			isvalid(char *str, int i);
	//	matrix_handler_utils.c
void		operators_core(char *str, t_program *shell, int *i, int *j);
void		operators_core_2(char *str, int *i, int *j, t_program *shell);
int			operators_allocation(char *str, t_program *shell, int i, int j);
	//	matrix_handler.c
int			matrix_handler(char *str, t_program *shell);
int			alloc_mtx_line(t_program *shell, char *str);
int			quotes_in_word(char *str, int *i);
int			matrix_handler_core(char *str, t_program *shell, int *i, int *j);
	//	parsing_checks_utils.c
int			double_operators(char *str);
void		skip(char *str, int *i);
int			check_operators(char *str, t_program *shell);
	//	parsing_checks.c
int			only_operator(char *str, t_program *shell);
int			near_operators(char *str);
void		near_operators_core(char *str, int *i, int *op);
int			check_quotes(char *str);
	//	parsing_utils_2.c
void		end_expansion2(t_program *shell, char \
*old_str, int *i, char **new_str);
int			expansion_variable2_core(t_program *shell, int *i, \
char *old_str, char **new_str);
int			first_expansion2_check(char *old_str, int *i);
char		*expansion_variable2(char *old_str, t_program *shell);
void		update_counter_and_i(int *i, int *counter);
	//	parsing_utils_3.c
int			count_new_matrix(char **mtx, int len);
int			only_dollar(char *str);
int			print_parsing_errors(int flag, t_program *shell);
	//	parsing_utils_4.c
int			static_check(char **old_str, int *i, char **new_str);
void		path_fuond(char **path, char **new_str);
void		expansion_variable2_else(int *i, char *old_str, char **new_str);
char		*ft_getenv(t_program *shell, char **sub_str);
int			only_spaces(char *str);
	//	parsing_utils_5.c
void		check_flag(int *flag_s, int *flag_d, char c);
int			check_pipe(char **mtx);
void		if_dollar(t_program *shell, int *k);
void		add_quote(char **new_str);
void		quotes_skips(char *str, int *i);
	//	parsing_utils.c
char		*remove_internal_quotes(char *old_str);
char		*remove_internal_quotes_core(char *old_str, int i, int *j);
char		*remove_all_quotes(char *old_str);
char		*remove_all_quotes_core(char *old_str, int i, int j);
	//	parsing.c
int			parsing(char *str, t_program *shell);
void		parsing_core_expansion(t_program *shell, int *k);
int			check_parsing_start(t_program *shell, char *str);
int			first_checks(char *str, t_program *shell);
char		**realloc_mtx_parsing(char **old_mtx, int len);
	//	quotes_core.c
int			quotes_core(char *str, t_program *shell, int *i_p, int *flag);
int			double_quote(char *str, t_program *shell, int *flag);
int			single_quote(char *str, t_program *shell, int *flag);

//	redirections
	//	expansions_in_hd.c
void		exec_dollar(char *str, t_program *shell, int fd);
int			exec_dollar_core(char *str, t_program *shell, int fd, int *i);
int			exec_dollar_core_2(t_program *shell, char *str, int fd, int *i);
void		search_env(char *env_str, t_program *shell, int fd);
	//	here_doc_utils_2.c
void		update_open_hd(t_program *shell, int fd, char *file, char *tmp);
	//	here_doc_utils.c
void		set_hd_g_signals(int flag);
void		close_here_doc(t_program *shell);
int			else_here_doc(t_program *shell, int id);
void		false_heredoc(t_program *shell, char *str);
int			is_there_a_single_quote(char *str);
	//	here_doc.c
int			open_here_doc(t_program *shell, char **mtx);
int			open_here_doc_while(int *i, t_program *shell, char **mtx);
int			open_here_doc_core(int *i, char **file, int *num_hd);
void		write_in_file(int fd, char *limiter, t_program *shell);
int			write_in_file_check(char **str, int *flag, \
char *limiter, t_program *shell);
	//	manage_in_out.c
int			counter_in_out(char c, char **mtx);
char		**realloc_without_redir(char **mtx, int k, char c);
void		initialize_files_in(int *i, int *j, int *num_hd, int flag);
	//	manage_input_utils.c
void		redir_input_clear(t_program *shell, char ***tmp, char ****mtx_hub);
	//	manage_input.c
int			redir_input(t_program *shell, int i, char ***mtx_hub, int flag);
int			open_files_in(char **mtx, t_program *shell);
int			open_file_in_hub(int *j, int *i, char **mtx, t_program *shell);
int			open_file_in_hd(int *i, int *j, int *num_hd, int *shell_in);
int			open_file_in_fd(int *i, int *j, char **mtx, t_program *shell);
	//	manage_output.c
int			redir_output(t_program *shell, int k, int i, char ***mtx_hub);
int			open_files_out(char **mtx, t_program *shell);
int			single_redirection(int *i, int *j, char **mtx, t_program *shell);
int			double_redirection(int *i, int *j, char **mtx, t_program *shell);
//	main_utils_4.c
void		realloc_expansion(t_program *shell);
void		skip_quotes(char *str, int *i);
int			need_to_correct_expansion(char *str);
//	main_utils_3.
void		case_space(char *str, int *i, int *init);
void		case_pipe(int *i, int *init, int *j, char **new_mtx);
void		update_realloc_2(char *str, int *i, int *init);
char		**alloc_expansion(char **new_mtx, char *str, int *j);
void		update_realloc(int j, t_program *shell, char **new_mtx);
//	main_utils_2.c
void		set_signals_pipe(t_program *shell);
int			readline_core(t_program *shell, char **str);
int			only_redir(char **mtx);
void		search_word(char *str, int *i);
//	main_utils.c
void		update_shlvl(t_program *shell);
char		*print_directory(t_program *shell);
int			initialize(t_program *shell);
void		free_all(t_program *shell, int flag);
//	main.c
void		correct_here_doc(t_program *shell);
int			flag_hd_decision(t_program *shell, int flag);
int			main_core(t_program *shell);
int			main_core_2(t_program *shell);
long long	ft_atol(char *nptr);

#endif