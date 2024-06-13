/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omougel <omougel@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:51:52 by omougel           #+#    #+#             */
/*   Updated: 2024/06/13 10:50:25 by omougel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <errno.h>
# define ERRMSG RED"Wrong input format\n" GRN"Please enter :\n./philo\
	\n\t<number of philosophers>\n\t<time to die>\n\t<time to eat>\
	\n\t<time to sleep>\
	\n\t[<number of time each philosopher must eat>] <- (last one optional)" RST

//*** colors ***

# define RST    "\033[0m"      /* Reset to default color */
# define RED	"\033[1;31m"   /* Bold Red */
# define GRN      "\033[1;32m"   /* Bold Green */
# define Y      "\033[1;33m"   /* Bold Yellow */
# define B      "\033[1;34m"   /* Bold Blue */
# define M      "\033[1;35m"   /* Bold Magenta */
# define C      "\033[1;36m"   /* Bold Cyan */
# define W      "\033[1;37m"   /* Bold White */

//*** OPCODE ***

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}			t_opcode;


typedef pthread_mutex_t t_mtx;
typedef struct s_table	t_table;

//*** strutures ***

/*
 * FORK
*/
typedef struct	s_fork
{
	t_mtx	fork;
	int		fork_id;
}				t_fork;

/*
 * PHILO
*/
typedef struct	s_philo
{
	int			id;
	long		meals_counter;
	bool		full;
	long		last_meal_time;
	t_fork		*first_fork;
	t_fork		*second_fork;
	pthread_t	thread_id;
	t_table		*table;
}				t_philo;

/*
 * TABLE
*/
struct s_table
{
	long philo_nbr;
	long time_to_die;
	long time_to_eat;
	long time_to_sleep;
	long nbr_limits_meals;
	long start_simulation;
	bool end_simulation;
	t_fork *forks;
	t_philo *philos;
};

//*** prototypes ***

// ** utils **
void  error_exit(const char *error);

// ** parsing **
void  parse_input(t_table *table, char **argv);

// ** safe functions **
void  *safe_malloc(size_t bytes);
void  safe_thread_handler(pthread_t *thread, void *(*func)(void *), void *data,
						  t_opcode opcode);
void  safe_mutex_handler(t_mtx *mutex, t_opcode opcode);

// ** init **
void  data_init(t_table *table);

#endif
