class Thread
{
public:
	Thread();
	~Thread();
	bool	createThread(void *(*)(void*), void *);

private:
	bool	joinThread();

private:
	pthread_t	_thread;
	/* data */
};