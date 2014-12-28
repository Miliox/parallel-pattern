/*
 * pipeline.h
 * Copyright (C) 2014  Emiliano Firmino <emiliano.firmino@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef __PIPELINE_H__
#define __PIPELINE_H__

#ifdef __unix__
    #include <pthread.h>

    #define THREAD_T pthread_t
    #define THREAD_FUNC(N, P) void* N (void* P)

    #define THREAD_INIT(T, F, P) pthread_create(&T, NULL, F, P)
    #define THREAD_JOIN(T) pthread_join(T, NULL)
    #define THREAD_DESTROY(T)

#elif WIN32
    #include <windows.h>

    #define THREAD_T HANDLE
    #define THREAD_FUNC(N, P) DWORD WINAPI N (LPVOID P)

    #define THREAD_INIT(T, F, P) T = CreateThread(NULL, 0, F, P, 0, NULL)
    #define THREAD_JOIN(T) WaitForSingleObject(T, INFINITE)
    #define THREAD_DESTROY(T) CloseHandle(T)
#else
#endif



#endif /* !__PIPELINE_H__ */

