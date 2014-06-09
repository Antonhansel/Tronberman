#ifndef THREAD_HPP_
# define THREAD_HPP_

# include <pthread.h>
# include <iostream>
# include "ScopedLock.hpp"

class Thread
{
public:
	Thread();
	Thread(ScopedLock *);
	~Thread();
	bool	createThread(void *(*start_routine)(void*), void *);
	bool	joinThread();

private:

private:
	pthread_t		_thread;
	pthread_mutex_t	*_mutex;
	ScopedLock		*_scopedLock;
	/* data */
};

#endif /* THREAD_HPP_ */