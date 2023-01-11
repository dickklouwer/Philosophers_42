/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tasks.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/11 14:09:26 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/01/11 15:35:37 by tklouwer      ########   odam.nl         */
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
    int i;

    i = 0;
    pthread_mutex_lock(data->write_mutex);
    curr_time = get_current_time();
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
    // pthread_mutex_lock(philo->data->write_mutex);
    if (done_eating(philo->data, philo) > 0)
        return (philo->done = 1, 1);
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
        pthread_mutex_unlock(philo->rfork);
        return (EXIT_FAILURE);
    }
    pthread_mutex_lock(philo->rfork);
    pick_fork(philo);
    philo->must_eat--;
    if (!died(data, philo))
        return (print_log(philo, DIED), 1);
    philo->time_last_eat = get_current_time();
    // pthread_mutex_unlock(philo.dat)
    p_sleep(philo, data->time_to_eat, EATING);
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
