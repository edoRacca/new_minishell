/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eraccane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 17:25:13 by eraccane          #+#    #+#             */
/*   Updated: 2023/11/14 19:06:28 by eraccane         ###   ########.fr       */
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
# include <sys/ioctl.h>
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_env {
	char	**env;
	char	*line;
	char	*path;
	int		exit_status;
}               t_env;

/*
----------- env_function.c ----------
*/
void    copy_env_line(char *dest, char *src);
int		size_env(char **env);
void	copy_env(t_env *e, char **env);
void	init_env(t_env *e, char **env);

#endif