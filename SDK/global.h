//
// Created by vinokurov on 04.12.2019.
//
#ifndef ENERGO_GLOBAL_H
#define ENERGO_GLOBAL_H

#ifdef SDK_EXPORT
#define EXPORTS __declspec(dllexport)
#else
#define EXPORTS __declspec(dllimport)
#endif

#endif //ENERGO_GLOBAL_H
