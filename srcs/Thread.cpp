Thread::Thread()
{
}

Thread::~Thread()
{}

bool	Thread::createThread(void *(*start_routine)(void*), void *arg)
{
	if (pthread_create(&_thread, NULL, &start_routine, arg) == 0)
		return (joinThread());
	return (false);
}

bool	Thread::joinThread()
{
	if (pthread_join(_thread, NULL) == 0)
		return (true);
	return (false);
}