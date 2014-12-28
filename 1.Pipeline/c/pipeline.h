/*
 * pipeline.h
 * Copyright (C) 2014  Emiliano Firmino <emiliano.firmino@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef __PIPELINE_H__
#define __PIPELINE_H__

#ifdef LINUX
    #include <pthread.h>

#elif WIN32
    #include <windows.h>

    #define THREAD_T HANDLE
    #define THREAD_FUNC(N, P) DWORD WINAPI N (LPVOID P)

    #define THREAD_INIT(T, F, P) T = CreateThread(NULL, 0, F, P, 0, NULL)
    #define THREAD_JOIN(T) WaitForSingleObject(T, INFINITE)
    #define THREAD_DESTROY CloseHandle(T)
#else
#endif



#endif /* !__PIPELINE_H__ */

