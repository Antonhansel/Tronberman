class ScopedLock
{
public:
	ScopedLock();
	~ScopedLock();

private:
	ScopedLock(const ScopedLock &);
	ScopedLock	&operator=(const ScopedLock &);

private:
	pthread_mutex_t		*_mutex;
};