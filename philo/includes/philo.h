/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/23 13:26:17 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/01/19 13:37:31 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
#include <stdlib.h>

typedef struct s_philo t_philo;
typedef struct s_data t_data;

# define EATING 1
# define FORK	2
# define SLEEPING 3
# define THINKING 4
# define DIED	5

typedef struct      s_philo
{
	int             id;
	int				done;
	long long int	must_eat;
	uint64_t        time_last_eat;
	t_data          *data;
	pthread_mutex_t *lfork;
	pthread_mutex_t *rfork;
	pthread_t		*philo_t;
}                   t_philo;

typedef struct      s_data
{
	int              	num_philos;
	long long int     		time_to_die;
	long long int     	time_to_eat;
	long long int    	time_to_sleep;
	long long int       n_must_eat;
	int					finished;
	uint64_t          	start_time;
	pthread_mutex_t	  	*chopsticks;
	pthread_mutex_t		*write_mutex;
	pthread_mutex_t		*data_mutex;
	t_philo           	*philo;
}           t_data;

void     died(t_data *data);
void     p_sleep(t_data *data, long long ms);
int     philo_sleep(t_philo *philo);
int parse_input(t_data *data, char **argv, int argc);
u_int64_t	get_current_time(void);
int print_log(t_philo *philo, int state);
void     died(t_data *data);

/*  LIBFT
 */
int	    ft_atoi(const char *str);
int	    error(char *str, int errnum);
void	*ft_calloc(size_t count, size_t size);
int     ft_isdigit(int c);

int philo_threads(t_data *data);

int only_num(char *str);

int 	thinking(t_philo *philo);
int    eating(t_philo *philo);
int 	pick_fork(t_philo *philo);

/* 
	DELETE WHEN FHINISED
 */
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
void	ft_putchar_fd(char c, int fd);
#endif