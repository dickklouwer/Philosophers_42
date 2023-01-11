/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philosophers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/04 15:05:22 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/01/10 14:38:02 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int     done_eating(t_data *data, t_philo *philo)
{
    long long int i;

    i = 0;
    if (philo->must_eat == -1)
        return (-1);
    if (philo->must_eat == 0)
    {
        while (i < data->num_philos)
        {
            if (data->philo[i].must_eat > 0)
                return (0);
            i++;
        }
    }
    return (1);
}

int     died(t_data *data, t_philo *philo)
{
    uint64_t curr_time;

    curr_time = get_current_time();
    if ((curr_time - philo->time_last_eat) > data->time_to_die)
        return (philo->done = 1, 1);
    return (EXIT_SUCCESS);
}

int pick_fork(t_philo *philo)
{
    if (done_eating(philo->data, philo) == 0)
        return (philo->done = 1, 1);
    print_log(philo, FORK);
    return (EXIT_SUCCESS);
}

int    eating(t_philo *philo)
{
    t_data *data;

    data = philo->data;
    
    philo->time_last_eat = get_current_time();
    if (died(data, philo))
        return (print_log(philo, DIED), 1);
    if (!done_eating(philo->data, philo))
        return (philo->done = 1, 1);
    pthread_mutex_lock(philo->lfork);
    if (philo->lfork == philo->rfork)
    {
        pthread_mutex_unlock(philo->rfork);
        return (EXIT_FAILURE);
    }
    pthread_mutex_lock(philo->rfork);
    pick_fork(philo);
    print_log(philo, EATING);
    p_sleep(philo, data->time_to_eat);
    philo->must_eat--;
    pthread_mutex_unlock(philo->lfork);
    pthread_mutex_unlock(philo->rfork);
    return (EXIT_SUCCESS);
}

int thinking(t_philo *philo)
{
    if (!done_eating(philo->data, philo))
        return (philo->done = 1);
    print_log(philo, THINKING);
}

void    *philo(void *philosopher)
{
    t_philo *philo;
    t_data *data;

    philo = (t_philo *)philosopher;
    data = philo->data;
    if (philo->id % 2 == 0)
    {
        p_sleep(philo, data->time_to_sleep);
        print_log(philo, SLEEPING);
    }
    while (philo->done == 0)
    {
        if (eating(philo))
            break ;
        thinking(philo);
    }
}

int philo_threads(t_data *data)
{
    int i;

    i = 0;
    data->start_time = get_current_time();
    while (i < data->num_philos)
    {
        data->philo[i].time_last_eat = data->start_time;
        if (pthread_create(data->philo_t, NULL, &philo, &data->philo[i]))
            return (EXIT_FAILURE);
        i++;
    }
}