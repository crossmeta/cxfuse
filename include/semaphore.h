/*
 * semaphore mapping to WIN32 for FUSE library
 * (C) Copyright 2012 Sammandam, Supramani suprasam@crossmeta.org
 */

#ifndef	_INCLUDE_SEMAPHORE_H
#define	_INCLUDE_SEMAPHORE_H

typedef HANDLE	sem_t;

static __inline HANDLE
sem_init(sem_t *sem, int pshared, int value)
{
	*sem = CreateEvent(NULL, FALSE, value, NULL);
	return 0;
}

static __inline int sem_wait(sem_t *sem)
{
	HANDLE h = *sem;
	return WaitForSingleObject(h, INFINITE);
}

static __inline int sem_post(sem_t *sem)
{
	HANDLE h = *sem;
	SetEvent(h);
}
	
static __inline int sem_destroy(sem_t *sem)
{
	return CloseHandle(*sem);
}
#endif
