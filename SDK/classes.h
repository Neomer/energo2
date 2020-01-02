//
// Created by vinokurov on 13.12.2019.
//

#ifndef ENERGO_CLASSES_H
#define ENERGO_CLASSES_H

#define STATIC_CLASS(class_name)      \
    public: \
        class_name() = delete; \
        class_name(const class_name &) = delete; \
        class_name(const class_name &&) = delete; \
        class_name &operator=(const class_name &) = delete; \
        class_name &operator=(const class_name &&) = delete;

#define SINGLETON_CLASS(class_name)      \
    private: \
        class_name(); \
    public: \
        class_name(const class_name &) = delete; \
        class_name(const class_name &&) = delete; \
        class_name &operator=(const class_name &) = delete; \
        class_name &operator=(const class_name &&) = delete;




#endif //ENERGO_CLASSES_H
