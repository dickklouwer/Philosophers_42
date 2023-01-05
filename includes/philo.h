/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/23 13:26:17 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/01/05 14:11:53 by tklouwer      ########   odam.nl         */
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

typedef struct      s_philo
{
    int             id;
    int             last_eat;
    t_data          *data;
    pthread_mutex_t *lfork;
    pthread_mutex_t *rfork;
}                   t_philo;

typedef struct      s_data
{
    int               num_philos;
    long long int     time_to_die;
    long long int     time_to_eat;
    long long int     time_to_sleep;
    int               n_must_eat;
    pthread_mutex_t   *chopsticks;
    t_philo           *philo;
}           t_data;

int parse_input(t_data *data, char **argv, int argc);

/*  LIBFT
 */
int	    ft_atoi(const char *str);
int	    error(char *str, int errnum);
void	*ft_calloc(size_t count, size_t size);
int     ft_isdigit(int c);

int ft_philosophers(t_data *data);

/* 
    DELETE WHEN FHINISED
 */
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
void	ft_putchar_fd(char c, int fd);
#endif