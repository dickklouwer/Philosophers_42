/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tasks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 14:09:26 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/01/13 15:21:28 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int     done_eating(t_data *data, t_philo *philo)
{
    long long int i;

    i = 0;
    if (philo->must_eat < 0)
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

int     died(t_data *data)
{
    uint64_t curr_time;
    int i;

    i = 0;
    while (1)
    {
        curr_time = get_current_time();
        if ((curr_time - data->philo[i % data->num_philos].time_last_eat) > data->time_to_die)
        {
            data->finished = 1;
            print_log(&data->philo[i % data->num_philos], DIED);
            return (EXIT_SUCCESS);
        }
        i++;
    }
    return (EXIT_SUCCESS);
}

int pick_fork(t_philo *philo)
{
    if (philo->data->finished)
        return (EXIT_FAILURE);
    print_log(philo, FORK);
    return (EXIT_SUCCESS);
}

int     sleeper(t_philo *philo)
{
    if (philo->data->finished)
        return (EXIT_FAILURE);
    p_sleep(philo, philo->time_last_eat, SLEEPING);
    return (EXIT_SUCCESS);
}

int    eating(t_philo *philo)
{
    t_data *data;

    data = philo->data;
    pthread_mutex_lock(philo->lfork);
    philo->done = pick_fork(philo);
    if (philo->lfork == philo->rfork)
    {
        pthread_mutex_unlock(philo->rfork);
        return (EXIT_FAILURE);
    }
    pthread_mutex_lock(philo->rfork);
    philo->done = pick_fork(philo);
    philo->time_last_eat = get_current_time();
    p_sleep(philo, data->time_to_eat, EATING);
    if (!done_eating(data, philo))
    {
        data->finished = 1;
        pthread_mutex_unlock(philo->lfork);
        pthread_mutex_unlock(philo->rfork);
        return (EXIT_FAILURE);
    }
    pthread_mutex_unlock(philo->lfork);
    pthread_mutex_unlock(philo->rfork);
    return (EXIT_SUCCESS);
}

int thinking(t_philo *philo)
{
    if (print_log(philo, THINKING))
        return (EXIT_FAILURE);
    return (0);
}
