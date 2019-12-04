//
// Created by vinokurov on 04.12.2019.
//
#ifndef ENERGO_GLOBAL_H
#define ENERGO_GLOBAL_H

#if defined(_MSC_VER)
#ifdef SDK_EXPORT
#define EXPORTS __declspec(dllexport)
#else
#define EXPORTS __declspec(dllimport)
#endif
#elif defined(__GNUC__)
#ifdef SDK_EXPORT
#define EXPORTS __attribute__((visibility("default")))
#else
#define EXPORTS
#endif
#else
    #define EXPORT
    #define IMPORT
    #pragma warning Unknown dynamic link import/export semantics.
#endif


#endif //ENERGO_GLOBAL_H
