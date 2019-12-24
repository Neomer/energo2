//
// Created by vinokurov on 24.12.2019.
//

#ifndef ENERGO_THREADSAFEARRAY_H
#define ENERGO_THREADSAFEARRAY_H

#include <atomic>
#include <mutex>
#include <cinttypes>
#include <stdexcept>
#include <cstring>

namespace energo::types {

/**
 * Реализация потокобезопасного массива статичного размера.
 * @tparam TElement Тип элемента массива.
 * @tparam NElements Количество элементов в массиве.
 */
template<typename TElement, size_t NElements>
class ThreadSafeArray {
    TElement _items[NElements];
    std::mutex _mtx;

    inline void assertIndex(size_t index) const {
        if (index >= NElements) {
            throw std::range_error("Индекс элемента выходит за границы допустимых значений.");
        }
    }

public:
    /**
     * Инициализиует массив.
     */
    ThreadSafeArray() = default;

    /**
     * Инициализирует массив.
     * @param args коллекция иницализирующих значений.
     */
    ThreadSafeArray(std::initializer_list<TElement> args)
    {
        auto it = args.begin();
        for (size_t idx = 0; it != args.end(); ++idx, ++it) {
            _items[idx] = *it;
        }
    }

    /**
     * возвращает константный указатель на элемент массива с индексом index.
     * @param index Индекс элемента массива.
     * @throws std::range_error Некорректный индекс элемента массива.
     * @return
     */
    const TElement &operator[] (size_t index) {
        return get(index);
    }

    /**
     * возвращает константный указатель на элемент массива с индексом index.
     * @param index Индекс элемента массива.
     * @throws std::range_error Некорректный индекс элемента массива.
     * @return
     */
    [[nodiscard]] const TElement &get(size_t index) {
        assertIndex(index);
        std::lock_guard grd(_mtx);
        return _items[index];
    }

    /**
     * Устанавливает значение элементу массива.
     * @param index Индекс элемента массива.
     * @param element Новое значение.
     * @throws std::range_error Некорректный индекс элемента массива.
     */
    void set(size_t index, const TElement &element) {
        assertIndex(index);
        std::lock_guard grd(_mtx);
        _items[index] = element;
    }

    /**
     * Копирует несколько элементов внутрь массива.
     * @param data массив элементов, из которого происходит копирование элементов.
     * @param sourceStartIndex Индекс в массиве, из которого происходит копирование, с которого необходимо начинать копирование элементов.
     * @param targetStartIndex Индекс в массиве, в который происходит копирование, с которого необходимо начинать копирование элементов.
     * @param count Количество копируемых элементов.
     */
    void copyFrom(const TElement *data, size_t sourceStartIndex, size_t targetStartIndex, size_t count) {
        size_t endIdx = targetStartIndex + count - 1;
        assertIndex(targetStartIndex);
        assertIndex(endIdx);

        std::lock_guard grd(_mtx);
        for (size_t targetIdx = targetStartIndex, sourceIdx = sourceStartIndex; targetIdx <= endIdx; ++targetIdx, ++sourceIdx) {
            _items[targetIdx] = data[sourceIdx];
        }
    }

    /**
     * Копирует несколько элементов внутрь массива.
     * @param other массив элементов, из которого происходит копирование элементов.
     * @param sourceStartIndex Индекс в массиве, из которого происходит копирование, с которого необходимо начинать копирование элементов.
     * @param targetStartIndex Индекс в массиве, в который происходит копирование, с которого необходимо начинать копирование элементов.
     * @param count Количество копируемых элементов.
     */
    void copyFrom(ThreadSafeArray &other, size_t sourceStartIndex, size_t targetStartIndex, size_t count) {
        size_t endIdx = targetStartIndex + count - 1;
        assertIndex(targetStartIndex);
        assertIndex(endIdx);
        assertIndex(sourceStartIndex + other.size() - 1);

        std::lock_guard grd(_mtx);
        std::lock_guard grdRemote(other._mtx);
        for (size_t targetIdx = targetStartIndex, sourceIdx = sourceStartIndex; targetIdx <= endIdx; ++targetIdx, ++sourceIdx) {
            _items[targetIdx] = other._items[sourceIdx];
        }
    }

    /**
     * Копирует несколько элементов внутрь массива.
     * @param data массив элементов, в который происходит копирование элементов.
     * @param sourceStartIndex Индекс в массиве, из которого происходит копирование, с которого необходимо начинать копирование элементов.
     * @param targetStartIndex Индекс в массиве, в который происходит копирование, с которого необходимо начинать копирование элементов.
     * @param count Количество копируемых элементов.
     */
    void copyTo(TElement *data, size_t sourceStartIndex, size_t targetStartIndex, size_t count) {
        size_t endIdx = sourceStartIndex + count - 1;
        assertIndex(sourceStartIndex);
        assertIndex(endIdx);

        std::lock_guard grd(_mtx);
        for (size_t sourceIdx = sourceStartIndex, targetIdx = targetStartIndex; sourceIdx <= endIdx; ++sourceIdx, ++targetIdx) {
            data[targetIdx] = _items[sourceIdx];
        }
    }

    /**
     * Копирует несколько элементов внутрь массива.
     * @param data массив элементов, в который происходит копирование элементов.
     * @param sourceStartIndex Индекс в массиве, из которого происходит копирование, с которого необходимо начинать копирование элементов.
     * @param targetStartIndex Индекс в массиве, в который происходит копирование, с которого необходимо начинать копирование элементов.
     * @param count Количество копируемых элементов.
     */
    void copyTo(ThreadSafeArray &other, size_t sourceStartIndex, size_t targetStartIndex, size_t count) {
        other.copyFrom(*this, targetStartIndex, sourceStartIndex, count);
    }

    /**
     * Очищает память, в которой расположен массив.
     */
    inline void clear() {
        memset(&_items, 0, NElements * sizeof(TElement));
    }

    /**
     * @return Максимальное количество элементов, которое можно разместить в массиве.
     */
    [[nodiscard]] inline size_t size() const noexcept {
        return NElements;
    }
};

}

#endif //ENERGO_THREADSAFEARRAY_H
