/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eblancha <eblancha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:35:17 by eblancha          #+#    #+#             */
/*   Updated: 2025/02/11 13:30:15 by eblancha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	else if (status == EINVAL && (LOCK == opcode || UNLOCK == opcode))
		error_exit("The value specified by mutex is invalid");
	else if (status == EINVAL && INIT == opcode)
		error_exit("The value specified by attr is invalid");
	else if (status == EDEADLK)
		error_exit("A deadlock would occur"
			" if the thread blocked waiting for mutex");
	else if (status == EPERM)
		error_exit("The current thread does not hold a lock on mutex");
	else if (status == ENOMEM)
		error_exit("The process cannot allocate"
			" enough memory to create another mutex");
	else if (status == EBUSY)
		error_exit("Mutex is locked");
}

void	mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if (LOCK == opcode)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (UNLOCK == opcode)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (INIT == opcode)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (DESTROY == opcode)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		error_exit("Wrong opcode for mutex handle");
}

static void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	else if (status == EAGAIN)
		error_exit("No resources to create another thread");
	else if (status == EPERM)
		error_exit("The caller does not have appropriate permission");
	else if (status == EINVAL && CREATE == opcode)
		error_exit("The value specified by attr is invalid");
	else if (status == EINVAL && (JOIN == opcode || DETACH == opcode))
		error_exit("The value specified by thread is not joinable");
	else if (status == ESRCH)
		error_exit("No thread could be found corresponding"
			" to that specified by the given thread ID");
	else if (status == EDEADLK)
		error_exit("A deadlock was detected or the value"
			" of thread specifies the calling thread");
}

void	thread_handle(pthread_t *thread, void *(*foo)(void *),
		void *data, t_opcode opcode)
{
	if (CREATE == opcode)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (JOIN == opcode)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit("Wrong opcode for thread handle");
}
