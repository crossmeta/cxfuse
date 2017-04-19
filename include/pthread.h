/*
 * pthread mapping to WIN32 sufficient for FUSE library
 * (C) Copyright 2012 Sammandam, Supramani suprasam@crossmeta.org
 */
#ifndef _PTHREAD_H
#define	_PTHREAD_H

#include <wtypes.h>
#include <winbase.h>
#include <sys/timeb.h>

#define	PTHREAD_MUTEX_INITIALIZER	{(void*)-1,-1,0,0,0,0}
typedef CRITICAL_SECTION	pthread_mutex_t;
typedef	HANDLE	pthread_t;
typedef	HANDLE	pthread_cond_t;
typedef void *	pthread_mutexattr_t;
typedef void *	pthread_attr_t;
typedef unsigned int pthread_key_t;

#define	pthread_sigmask(x,y,z)
#define	pthread_setcancelstate(f,a)
#define	pthread_kill(t,s)	(0)
#define	pthread_cancel(t)
#define	pause()		WaitForSingleObject(pthread_self(), INFINITE)

#define	pthread_self(void)	GetCurrentThreadId()
#define	pthread_join(t, rv)	WaitForSingleObject(t, INFINITE)
#define	pthread_detach(t)		(0)
#define	pthread_attr_init(a)		(0)
#define	pthread_attr_setstacksize(a, sz)	(0)
#define	pthread_attr_destroy(a)		(0)

#define	pthread_key(t,v)	DWORD v
#define	pthread_key_create(k,f)	((*(k) = TlsAlloc()) == 0xFFFFFFFF)
#define	pthread_key_delete(k)	TlsFree(k)
#define	pthread_getspecific(k)	TlsGetValue(k)
#define	pthread_setspecific(k,v)	TlsSetValue(k,v)

static __inline void pthread_mutex_init(pthread_mutex_t *m,
				pthread_mutexattr_t *a)
{
	InitializeCriticalSection(m);
	return (0);
}

static __inline int pthread_mutex_lock(pthread_mutex_t *m)
{
	EnterCriticalSection(m);
	return (0);
}
	
static __inline int pthread_mutex_unlock(pthread_mutex_t *m)
{
	LeaveCriticalSection(m);
	return (0);
}

static __inline int pthread_mutex_destroy(pthread_mutex_t *m)
{
	DeleteCriticalSection(m);
}

static __inline int pthread_cond_init(pthread_cond_t *c, pthread_mutexattr_t *a)
{
	*c = CreateEvent(NULL, FALSE, FALSE, NULL);
	return (0);
}
static __inline int pthread_cond_destroy(pthread_cond_t *c)
{
	return CloseHandle(*c);
}

static __inline int pthread_cond_wait(pthread_cond_t *c, pthread_mutex_t *m)
{
	pthread_mutex_unlock(m);
	WaitForSingleObject(c, INFINITE);
	pthread_mutex_lock(m);
	return (0);
}

static __inline int
pthread_cond_timedwait(pthread_cond_t *c, pthread_mutex_t *m,
		const struct timespec *abstime)
{
	u_int64_t time_ms;
	u_int64_t cur_ms;
	struct __timeb64 tb;

	time_ms = abstime->tv_sec * 1000 + abstime->tv_nsec / 1000000;
	_ftime64(&tb);
	cur_ms = tb.time * 1000 + tb.millitm;
	if (time_ms <= cur_ms)
		return 0;
		
	pthread_mutex_unlock(m);
	WaitForSingleObject(c, (time_ms - cur_ms));
	pthread_mutex_lock(m);
}

static __inline int pthread_cond_signal(pthread_cond_t *c)
{
	SetEvent(c);
}

static __inline int pthread_cond_broadcast(pthread_cond_t *c)
{
	SetEvent(c);
}

static __inline int
pthread_create(pthread_t *th, pthread_attr_t *attr, LPTHREAD_START_ROUTINE func,
		void *arg)
{
	HANDLE h;
//	fprintf(stderr, "CreateThread arg %p\n", arg);
	h = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)func, arg, 0, NULL);
	if (!h)
		return GetLastError();
	return (0);
}

#endif
