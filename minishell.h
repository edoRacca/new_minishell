/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:25:13 by eraccane          #+#    #+#             */
/*   Updated: 2023/12/14 12:19:05 by eraccane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
readline = Legge una riga di input dalla console inserita dall'utente.
--------------------------------------------------------------------
rl_clear_history =  Cancella la cronologia degli input della riga di comando.
--------------------------------------------------------------------
rl_on_new_line = Notifica la libreria readline che
il cursore è su una nuova riga.
--------------------------------------------------------------------
rl_replace_line = Sostituisce l'intera riga corrente con una nuova
riga di testo.
--------------------------------------------------------------------
rl_redisplay = Aggiorna lo schermo per riflettere le
modifiche apportate alla riga di comando.
--------------------------------------------------------------------
add_history = Aggiunge una riga di input alla cronologia
degli input della riga di comando.
--------------------------------------------------------------------
printf = Stampa a schermo.
--------------------------------------------------------------------
malloc = Alloca memoria.
--------------------------------------------------------------------
free = Libera memoria.
--------------------------------------------------------------------
write = Scrive un numero di caratteri.
--------------------------------------------------------------------
access = Verifica se un file ha determinati permessi di accesso.
--------------------------------------------------------------------
open = Apre un file o crea un file descriptor.
--------------------------------------------------------------------
read = Legge un certo numero di byte da un file descriptor.
--------------------------------------------------------------------
close = Chiude un file descriptor.
--------------------------------------------------------------------
fork = Crea un nuovo processo duplicando il processo corrente.
--------------------------------------------------------------------
wait = Sospende l'esecuzione del processo
chiamante fino al termine di un processo figlio.
--------------------------------------------------------------------
waitpid = Sospende l'esecuzione
del processo chiamante fino al termine di un processo specifico.
--------------------------------------------------------------------
wait3, wait4 = Funzioni simili a waitpid, ma con opzioni aggiuntive.
--------------------------------------------------------------------
signal = Imposta un gestore di segnale per un determinato segnale.
--------------------------------------------------------------------
sigaction = Imposta un gestore di segnale più
flessibile per un determinato segnale.
--------------------------------------------------------------------
sigemptyset = Inizializza un insieme di segnali vuoto.
--------------------------------------------------------------------
sigaddset = Aggiunge un segnale a un insieme di segnali.
--------------------------------------------------------------------
kill = Invia un segnale a un processo o a un gruppo di processi.
--------------------------------------------------------------------
exit = Termina immediatamente il processo corrente.
--------------------------------------------------------------------
getcwd = Restituisce il percorso della directory di lavoro corrente.
--------------------------------------------------------------------
chdir = Cambia la directory di lavoro corrente.
--------------------------------------------------------------------
stat ,lstat ,fstat = Restituiscono informazioni su un file o una directory.
--------------------------------------------------------------------
unlink = Rimuove un file o un link simbolico.
--------------------------------------------------------------------
execve = Esegue un programma specificato da un percorso di file.
--------------------------------------------------------------------
dup = duplica un file descriptor.
--------------------------------------------------------------------
dup2 = duplica un file descriptor su un
altro file descriptor specifico.
--------------------------------------------------------------------
pipe = crea una coppia di file descriptor per la comunicazione tra processi.
--------------------------------------------------------------------
opendir = apre una directory.
--------------------------------------------------------------------
readdir = legge una voce dalla directory.
--------------------------------------------------------------------
closedir = chiude una directory precedentemente aperta con opendir.
--------------------------------------------------------------------
strerror = restituisce una stringa descrittiva per un numero di errore.
--------------------------------------------------------------------
perror = stampa un messaggio di errore seguito da una
stringa descrittiva per un numero di errore.
--------------------------------------------------------------------
isatty = verifica se un file descriptor si riferisce a un terminale.
--------------------------------------------------------------------
ttyname = restituisce il nome del terminale associato a un file descriptor.
--------------------------------------------------------------------
ttyslot = restituisce lo slot del terminale associato a un file descriptor.
--------------------------------------------------------------------
ioctl = esegue operazioni di controllo del dispositivo su un file descriptor.
--------------------------------------------------------------------
getenv = ottiene il valore di una variabile d'ambiente.
--------------------------------------------------------------------
tcsetattr = imposta i parametri del terminale.
--------------------------------------------------------------------
tcgetattr = ottiene i parametri del terminale.
--------------------------------------------------------------------
tgetent =  inizializza la libreria terminfo.
--------------------------------------------------------------------
tgetflag = ottiene il valore di una flag terminfo.
--------------------------------------------------------------------
tgetnum = ottiene il valore di una capacità numerica terminfo.
--------------------------------------------------------------------
tgetstr = ottiene il valore di una capacità di stringa terminfo.
--------------------------------------------------------------------
tgoto = costruisce una sequenza di escape terminfo
per un determinato movimento del cursore.
--------------------------------------------------------------------
tputs = invia una sequenza di escape terminfo alla console.
*/

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/* -- TOKEN TYPE -- */
# define EMPTY 0
# define PATH 1
# define BUILT 2
# define NOBUILT 3
# define FLAG 4
# define ARG 5
# define PIPE 6
# define TRUNC 7
# define APPEND 8
# define INPUT 9
# define HDOC 10

/* -- STD -- */
# define STDIN 0
# define STDOUT 1
# define STDERR 2

/* -- EXIT CODE -- */
# define ERROR 1
# define SUCCESS 0
# define DIRECTORY 126
# define UNKNOWN_CMD 127

typedef struct s_token
{
	char			*string;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_env
{
	char			**env;
	char			*line;
	char			*path;
	char			*cmd_path;
	char			**flag_matrix;
	char			*hdoc_str;
	int				exit_status;
	int				exit;
	int				quotes;
	int				flag_quotes;
	int				pipe_quotes;
	int				red_quotes;
	int				redir;
	int				quotes_open;
	int				status;
	int				hdoc;
	int				count_pipe;
	int				count_redir;
	int				pipe_fd[2];
	int				pid_pipe;
	int				stdin;
	int				stdout;
	t_token			*tokens;
}					t_env;

/*
** echo_2.c
*/
void				else_quotes_format(t_env *e);
void				check_closure(t_env *e, t_token *tokens, char quote);
void				quotes_format(t_env *e);
int					check_redir(t_env *e);

/*
** echo.c
*/
void				echo_quotes(t_env *e, t_token *start);
int					find_inenv(char **env, char *str);
void				echo_expansion(t_env *e);
void				last_echo_cmd(t_env *e);
void				echo_cmd(t_env *e);

/*
** env_function.c **
*/
void				copy_line(char *dest, char *src);
int					size_env(char **env);
void				copy_env(t_env *e, char **env);
void				print_env(char **env);
void				init_env(t_env *e, char **env);

/*
** error_exit_2.c
*/
void				invalid_identif(t_env *e);

/*
** error_exit.c
*/
void				cmd_notfound(t_env *e);
void				fdir_notfound(t_env *e, int type);
void				too_many_args(t_env *e);
void				too_few_args(t_env *e);
void				exiting(t_env *e, int ex);

/*
** executing_2.c
*/
void				waiting(t_env *e, pid_t pid);
void				exec_cmd(t_env *e);
void				alloc_cmd_path(t_env *e);
void				alloc_flagmatrix(t_env *e);
void				nobuilt_command(t_env *e);

/*
** executing.c
*/
void				last_built_nobuilt(t_env *e);
void				other_builtin_cmd(t_env *e);
void				builtin_cmd(t_env *e);
void				cmd_type(t_env *e);
void				executing(t_env *e);

/*
** export_2.c
*/
char				**copy_env_temp(char **env, char **dest, char *str);
char				**alloc_diff_var(char **env, char **tmp_e, char *str);
void				over_exp_var(t_env *e, char *str);

/*
** export.c
*/
char				*rewrite_arg(char *str);
int					exp_var_exists(t_env *e, char *str);
void				export_var(t_env *e, char *str, int flag);
void				parsing_exp_var(t_env *e);
void				export_function(t_env *e);

/*
** history.c **
*/
void				print_history(void);

/*
** main.c
*/
int					pre_exec_2(t_env *e);
void				pre_exec(t_env *e);

/*
** multiple_redirect.c
*/
t_token	*find_last_out(t_env *e);
t_token	*find_last_in(t_env *e);
void	multiple_redir(t_env *e);

/*
** parsing.c **
*/
int					not_builtin_cmd(char *word);
int					is_builtin_cmd(char *word);
void				select_type(t_token *token, char *word);
void				parsing(t_env *e);

/*
** path_functions.c **
*/
int					find_path(char *str);
void				set_cmdpath(t_env *e, int i, int j);
void				copy_path(t_env *e, int i, int j);
void				cmd_path(t_env *e);
void				search_path(t_env *e);

/*
** pipe_2.c
*/
t_token				*update_pipe(t_env *e);
void				parent_command(t_env *e);
void				parent_process(t_env *e);
void				fork_loop(t_env *e);

/*
** pipe.c
*/
void				multiple_pipe(t_env *e);
void				piping(t_env *e);
int					is_pipe_inquote(char *str);
int					pipe_between(t_token *tk);
int					count_pipe(t_env *e);

/*
** redir_hdoc.c
*/
int					check_error_red(int pipe_fd[2]);
char				*update_buffer(char *line, char *buffer);
void				print_hdoc_continue(t_env *e, char *s, int pipe_fd[2],
						pid_t pid);
void				print_redir_hdoc(t_env *e, char *buffer);

/*
** redir_input.c
*/
void				input_continue_2(t_env *e, int fd, pid_t pid);
void				input_continue(t_env *e, int fd);

/*
** redir_trunc.c
*/
void				fork_redir(t_env *e, char *filename, int type);
void				redir_fork(t_env *e, char *filename, int type);

/*
** redirections.c
*/
int					count_redirection(t_env *e);
void				redirect_trunc(t_env *e);
void				redirect_append(t_env *e);
void				redirect_input(t_env *e);
void				redirect_hdoc(t_env *e);
/*
** signals.c **
*/
void				signals(t_env *e);
void				ctrl_d(t_env *e);
int					signals_hdoc(char *line, char *delimiter, char *buffer);

/*
** syntax_2.c
*/
t_token				*redir_in_quotes(t_env *e, t_token *tokens, int i);
int					check_closure_redir(t_env *e, t_token *start, char quotes);
t_token				*quotes_redirect(t_env *e, t_token *start);
int					check_closure_pipe(t_env *e, t_token *start, char quotes);

/*
** syntax.c
*/
int					search_pipe(t_env *e);
int					invalid_pipe(t_env *e);
int					invalid_cmd(t_env *e);
int					invalid_syntax(t_env *e);

/*
** token_funtions_2.c
*/
t_token				*start_token(t_token *tokens);
t_token				*find_first_token(t_token *token);
void				print_tokens(t_token *tokens);

/*
** token_funtions.c
*/
t_token				*find_last_token(t_token *token);
void				addback_token_node(t_token **token, t_token *new);
t_token				*new_token_node(char *word);
void				init_tokens(t_env *e, char **cmd_line);
void				free_tokens(t_token **tokens);

/*
** unset.c
*/
int					unset_var_name(char *var_e, char *var);
char				**unset_copy_env(char **env, char **dest, char *var);
void				unset_function(t_env *e);

/*
** utils_6.c
*/
char				*ft_putstr(const char *s);
char				*alloc_str(char *s);
char				*ft_strcpy_n(char *dest, const char *src);
void				continue_join_n(char *st, char *s1, char *s2);
char				*ft_strjoin_n(char *s1, char *s2);

/*
** utils_5.c
*/
int					check_if_open(t_token *tokens, int start);
int					is_redir_inquote(char *str);
int					redir_between(t_env *e);
int					last_redir(t_token *tokens);
int					check_quotes_red(char *str, char quotes);

/*
** utils_4.c
*/
char				quote_type(char *str);
void				redir_free(t_env *e);
char				*find_filename(t_env *e);
int					search_arrows(t_env *e);
char				*put_cmd(t_env *e, char *cmd);

/*
** utils_3.c
*/
void				echo_print_str(char *str, int start);
int					empty_cmd(t_env *e);
int					count_flag(t_env *e);
void				print_argtype(t_env *e);
int					cmd_len(char *str);

/*
** utils_2.c
*/
int					find_dollar(char *str);
int					check_equal(char *str);
int					is_all_alpha(char *str);
int					exp_var_name(char *var, char *newvar);
int					env_var_len(char *str);

/*
** utils.c **
*/
void				print_matrix(char **matrix);
void				free_matrix(char **str);
int					str_cmp(char *s1, char *s2);
int					check_quotes_closed(char *str, int start);
int					check_quotes(char *str);

#endif