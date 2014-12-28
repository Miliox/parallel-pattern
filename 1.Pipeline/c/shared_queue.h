/*
 * shared_queue.h
 * Copyright (C) 2014 Emiliano Firmino <emiliano.firmino@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef __SHARED_QUEUE_H__
#define __SHARED_QUEUE_H__

#ifdef __unix__
    #include <semaphore.h>
    #include <stdlib.h>
    #include <string.h>
    #include <pthread.h>

    #define MUTEX_T          pthread_mutex_t
    #define MUTEX_INIT(M)    pthread_mutex_init(&M, NULL)
    #define MUTEX_LOCK(M)    pthread_mutex_lock(&M)
    #define MUTEX_UNLOCK(M)  pthread_mutex_unlock(&M)
    #define MUTEX_DESTROY(M) pthread_mutex_destroy(&M)

    #define SEM_T          sem_t
    #define SEM_INIT(S)    sem_init(&S, 0, 0)
    #define SEM_UP(S)      sem_post(&S)
    #define SEM_DOWN(S)    sem_wait(&S)
    #define SEM_DESTROY(S) sem_close(&S)

#elif WIN32
    #include <limits.h>
    #include <windows.h>

    #define MUTEX_T HANDLE
    #define MUTEX_INIT(M)    M = CreateMutex(NULL, FALSE, NULL)
    #define MUTEX_LOCK(M)    WaitForSingleObject(M, INFINITE)
    #define MUTEX_UNLOCK(M)  ReleaseMutex(M)
    #define MUTEX_DESTROY(M) CloseHandle(M)

    #define SEM_T HANDLE
    #define SEM_INIT(S)    S = CreateSemaphore(NULL, 0, INT_MAX, NULL)
    #define SEM_UP(S)      ReleaseSemaphore(S, 1, NULL)
    #define SEM_DOWN(S)    WaitForSingleObject(S, INFINITE)
    #define SEM_DESTROY(S) CloseHandle(S)
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
    SEM_T sem;
} shared_queue_t;

int shared_queue_init(
    shared_queue_t *queue, int size, size_t element_size);

int shared_queue_put(shared_queue_t *queue, void *element);
int shared_queue_pop(shared_queue_t *queue, void *element);

int shared_queue_is_empty(shared_queue_t *queue);
int shared_queue_is_full(shared_queue_t *queue);

int shared_queue_destroy(shared_queue_t *queue);

#endif /* !__SHARED_QUEUE_H__ */

