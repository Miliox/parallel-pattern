/*
 * pipeline.c
 * Copyright (C) 2014  Emiliano Firmino <emiliano.firmino@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "pipeline.h"
#include "shared_queue.h"

#include <stdio.h>

#define N 100

THREAD_FUNC(enqueue_thread_main, param) {
    shared_queue_t * q = param;

    for (int i = 0; i < N; i++) {
        printf("put %d\n", i);
        shared_queue_put(q, &i);
    }

    return 0;
}

THREAD_FUNC(dequeue_thread_main, param) {
    shared_queue_t * q = param;

    int v = 0;
    for (int i = 0; i < N; i++) {
        shared_queue_pop(q, &v);
        printf("pop %d\n", v);
    }

    return 0;
}

int main(int argc, char ** argv) {
    shared_queue_t q;
    shared_queue_init(&q, N, sizeof(int));

    THREAD_T enqueue_thread;
    THREAD_T dequeue_thread;

    THREAD_INIT(enqueue_thread, enqueue_thread_main, &q);
    THREAD_INIT(dequeue_thread, dequeue_thread_main, &q);

    THREAD_JOIN(enqueue_thread);
    THREAD_JOIN(dequeue_thread);

    shared_queue_destroy(&q);
    return 0;
}

