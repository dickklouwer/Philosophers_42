/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   die.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/19 13:03:12 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/01/19 13:04:28 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void     died(t_data *data)
{
    uint64_t curr_time;
    long long int i;

    i = 0;
    while (1)
    {
        pthread_mutex_lock(data->write_mutex);
        curr_time = get_current_time();
        if ((curr_time - data->philo[i % data->num_philos].time_last_eat) > (uint64_t) data->time_to_die)
        {
            print_log(&data->philo[i % data->num_philos], DIED);
            pthread_mutex_unlock(data->write_mutex);
            break ;
        }
        i++;
        pthread_mutex_unlock(data->write_mutex);
    }
}