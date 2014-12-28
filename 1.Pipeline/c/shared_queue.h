/*
 * shared_queue.h
 * Copyright (C) 2014 Emiliano Firmino <emiliano.firmino@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef __SHARED_QUEUE_H__
#define __SHARED_QUEUE_H__

#ifdef LINUX
#include <pthread.h>
#define MUTEX_T pthread_mutex_t
#define MUTEX_INIT(M) M = (pthread_mutex_init(&M, NULL) == 0) ? M : NULL
#define MUTEX_LOCK(M) pthread_mutex_lock(&M)
#define MUTEX_UNLOCK(M) pthread_mutex_unlock(&M)
#define MUTEX_DESTROY(M) CloseHandle(M)
#elif WIN32
#include <windows.h>
#define MUTEX_T HANDLE
#define MUTEX_INIT(M) M = CreateMutex(NULL, FALSE, NULL)
#define MUTEX_LOCK(M) WaitForSingleObject(M, INFINITE)
#define MUTEX_UNLOCK(M) ReleaseMutex(M)
#define MUTEX_DESTROY(M)
#else
#endif

#define SQ_SUCESS       0
#define SQ_INVALID_ARG -1
#define SQ_NO_RESOURCE -2

typedef struct shared_queue
{
    int size;
    int first;
    int last;

    size_t element_size;
    void   *elements;

    MUTEX_T mutex;
} shared_queue_t;

int shared_queue_init(
    shared_queue_t *queue, int size, size_t element_size);

int shared_queue_put(shared_queue_t *queue, void *element);

int shared_queue_pop(shared_queue_t *queue, void *element);

int shared_queue_is_empty(shared_queue_t *queue);

int shared_queue_is_full(shared_queue_t *queue);

int shared_queue_destroy(shared_queue_t *queue);

#endif /* !__SHARED_QUEUE_H__ */

