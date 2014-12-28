/*
 * pipeline.c
 * Copyright (C) 2014  Emiliano Firmino <emiliano.firmino@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "pipeline.h"
#include "shared_queue.h"

#include <stdio.h>

int main(int argc, char ** argv) {
    shared_queue_t q;
    shared_queue_init(&q, 5, sizeof(int));

    if (!shared_queue_is_empty(&q))
        printf("queue is not empty");

    shared_queue_put(&q, &(int){1});
    shared_queue_put(&q, &(int){2});
    shared_queue_put(&q, &(int){3});
    shared_queue_put(&q, &(int){4});
    shared_queue_put(&q, &(int){5});

    if (!shared_queue_is_full(&q))
        printf("queue is not full");

    int v = 0;

    shared_queue_pop(&q, &v);
    printf(" %d", v);
    shared_queue_pop(&q, &v);
    printf(" %d", v);
    shared_queue_pop(&q, &v);
    printf(" %d", v);
    shared_queue_pop(&q, &v);
    printf(" %d", v);
    shared_queue_pop(&q, &v);
    printf(" %d", v);

    if (!shared_queue_is_empty(&q))
        printf("queue is not empty");

    shared_queue_destroy(&q);
    return 0;
}

