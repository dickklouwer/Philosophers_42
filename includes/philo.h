/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/23 13:26:17 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/01/10 15:17:58 by tklouwer      ########   odam.nl         */
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
}                   t_philo;

typedef struct      s_data
{
	int               num_philos;
	uint64_t     time_to_die;
	long long int     time_to_eat;
	long long int     time_to_sleep;
	int               n_must_eat;
	uint64_t          start_time;
	pthread_mutex_t	  *chopsticks;
	pthread_mutex_t		*write_mutex;
	t_philo           	*philo;
	pthread_t			*philo_t;
}           t_data;

void     p_sleep(t_philo *philo, uint64_t ms);
int parse_input(t_data *data, char **argv, int argc);
u_int64_t	get_current_time(void);
void print_log(t_philo *philo, int state);
int     died(t_data *data, t_philo *philo);

/*  LIBFT
 */
int	    ft_atoi(const char *str);
int	    error(char *str, int errnum);
void	*ft_calloc(size_t count, size_t size);
int     ft_isdigit(int c);

int philo_threads(t_data *data);

int only_num(char *str);

/* 
	DELETE WHEN FHINISED
 */
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
void	ft_putchar_fd(char c, int fd);
#endif