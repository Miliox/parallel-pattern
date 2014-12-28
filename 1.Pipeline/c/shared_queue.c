/*
 * shared_queue.c
 * Copyright (C) 2014 Emiliano Firmino <emiliano.firmino@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "shared_queue.h"

int shared_queue_init(
    shared_queue_t *queue, int size, size_t element_size) {

    if (size <= 0 || element_size <= 0)
        return SQ_INVALID_ARG;

    void *buffer = calloc(size, element_size);

    if (buffer == NULL)
        return SQ_NO_RESOURCE;

    MUTEX_T mutex;
    MUTEX_INIT(mutex);

    if (mutex == NULL) {
        free(buffer);
        return SQ_NO_RESOURCE;
    }

    SEM_T sem;
    SEM_INIT(sem);

    if (sem == NULL) {
        free(buffer);
        MUTEX_DESTROY(mutex);
    }

    queue->size = size + 1;
    queue->first = 0;
    queue->last = 0;
    queue->element_size = element_size;
    queue->elements = buffer;
    queue->mutex = mutex;
    queue->sem = sem;

    return SQ_SUCESS;
}

int shared_queue_put(shared_queue_t *q, void *element) {
    MUTEX_LOCK(q->mutex);

    void * dest = ((char*) q->elements) + (q->last * q->element_size);
    memcpy(dest, element, q->element_size);
    q->last = (q->last + 1) % q->size;

    if (q->last == q->first)
        q->first = (q->first + 1) % q->size;

    MUTEX_UNLOCK(q->mutex);
    SEM_UP(q->sem);
    return SQ_SUCESS;
}

int shared_queue_pop(shared_queue_t *q, void *element) {
    SEM_DOWN(q->sem);
    MUTEX_LOCK(q->mutex);

    void * src = ((char*) q->elements) + (q->first * q->element_size);
    memcpy(element, src, q->element_size);
    q->first = (q->first + 1) % q->size;

    MUTEX_UNLOCK(q->mutex);
    return SQ_SUCESS;
}

int shared_queue_is_empty(shared_queue_t *q) {
    MUTEX_LOCK(q->mutex);

    int is_empty = q->last == q->first;

    MUTEX_UNLOCK(q->mutex);
    return is_empty;
}

int shared_queue_is_full(shared_queue_t *q) {
    MUTEX_LOCK(q->mutex);

    int is_full = (q->last + 1) % q->size == q->first;

    MUTEX_UNLOCK(q->mutex);
    return is_full;
}

int shared_queue_destroy(shared_queue_t *q) {
    MUTEX_LOCK(q->mutex);
    free(q->elements);
    MUTEX_UNLOCK(q->mutex);
    MUTEX_DESTROY(q->mutex);
    SEM_DESTROY(q->sem);
    return SQ_SUCESS;
}
