//
// Created by vinokurov on 05.12.2019.
// Макросы для определения типа операционной системы, разрядности процессора и т.д.
//

#ifndef ENERGO_OS_H
#define ENERGO_OS_H

#if _WIN32 || _WIN64
#if _WIN64
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif
#endif

#if __GNUC__
#if __x86_64__ || __ppc64__
#define ENVIRONMENT64
#else
#define ENVIRONMENT32
#endif
#endif

#ifdef __linux__
#define OS_LINUX
#elif _WIN32
#define OS_WIN
#elif Macintosh || (__APPLE__ && __MACH__)
#define OS_MAC
#else
#error "Operation system isn't supported!"
#endif


#endif //ENERGO_OS_H
