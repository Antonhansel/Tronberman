#ifndef SCOPED_LOCK_HPP_
# define SCOPED_LOCK_HPP_

# include <pthread.h>

class ScopedLock
{
public:
	ScopedLock(pthread_mutex_t *);
	~ScopedLock();

private:
	ScopedLock(const ScopedLock &);
	ScopedLock	&operator=(const ScopedLock &);

private:
	pthread_mutex_t		*_mutex;
};

#endif /* SCOPED_LOCK_HPP_ */