/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tasks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 14:09:26 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/01/12 13:51:51 by tklouwer      ########   odam.nl         */
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
            if (died(data, &philo[i]))
                return (print_log(&philo[i], DIED), 0);
            i++;
        }
    }
    return (1);
}

int     died(t_data *data, t_philo *philo)
{
    uint64_t curr_time;
    int i;

    i = 0;
    
    curr_time = get_current_time();
    pthread_mutex_lock(data->write_mutex);
    if ((curr_time - philo->time_last_eat) > data->time_to_die)
    {
        pthread_mutex_unlock(data->write_mutex);
        return (philo->done = 1, 1);
    }
    pthread_mutex_unlock(data->write_mutex);
    return (EXIT_SUCCESS);
}

int pick_fork(t_philo *philo)
{
    pthread_mutex_lock(philo->data->write_mutex);
    print_log(philo, FORK);
    return (EXIT_SUCCESS);
}

int    eating(t_philo *philo)
{
    t_data *data;

    data = philo->data;
    pthread_mutex_lock(philo->lfork);
    pick_fork(philo);
    if (philo->lfork == philo->rfork)
    {
        pthread_mutex_unlock(philo->data->write_mutex);
        pthread_mutex_unlock(philo->rfork);
        return (EXIT_FAILURE);
    }
    pthread_mutex_lock(philo->rfork);
    pick_fork(philo);
    p_sleep(philo, data->time_to_eat, EATING);
    if (!done_eating(data, philo))
    {
        data->finished = 1;
        pthread_mutex_unlock(philo->data->write_mutex);
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
    print_log(philo, THINKING);
    return (philo->done = 0, 0);
}
