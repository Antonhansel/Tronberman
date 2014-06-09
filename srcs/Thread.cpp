#include "Thread.hpp"

Thread::Thread()
{
	pthread_mutex_t 	mutex = PTHREAD_MUTEX_INITIALIZER;

	_mutex = &mutex;
	//_scopedLock = new ScopedLock(_mutex);
}

Thread::Thread(pthread_mutex_t *mutex) :
	_mutex(mutex)
{
	//_scopedLock = new ScopedLock(_mutex);
}

Thread::~Thread()
{
	//delete _scopedLock;
}

bool	Thread::createThread(void *(*start_routine)(void*), void *arg)
{
	if (pthread_create(&_thread, NULL, start_routine, arg) == 0)
		return (/*joinThread()*/true);
	return (false);
}

bool	Thread::joinThread()
{
	if (pthread_join(_thread, NULL) == 0)
		return (true);
	return (false);
}