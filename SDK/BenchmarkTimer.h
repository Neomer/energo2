//
// Created by vinokurov on 11.12.2019.
//

#ifndef ENERGO_BENCHMARKTIMER_H
#define ENERGO_BENCHMARKTIMER_H

#include <ostream>
#include <string_view>
#include <string>
#include <chrono>
#include "os.h"

namespace energo::benchmark {

/**
 * Класс для организации проверки быстродействия.
 * Для использования необходимо создать экземпляр класса, при удалении будет выведена информация о времени жизни объекта.
 */
class BenchmarkTimer {
    std::chrono::time_point<std::chrono::high_resolution_clock> _startPoint, _lap;
    std::ostream &_stream;
    std::string_view _benchName;
    bool _stopped;

public:
    /**
     * Создать новый бенчмарк.
     * @param stream Поток для вывода информации о тестировании.
     */
    explicit BenchmarkTimer(std::ostream &stream);

    /**
     * Создать новый бенчмарк.
     * @param benchmarkName Наименование бенчмарка. Будет выведено вместе с резуьлтатами.
     * @param stream Поток для вывода информации о тестировании.
     */
    explicit BenchmarkTimer(std::string_view benchmarkName, std::ostream &stream);

    /**
     * Создать новый бенчмарк. вывод будет осуществляться в stdout.
     * @param benchmarkName
     */
    explicit BenchmarkTimer(std::string_view benchmarkName);

    ~BenchmarkTimer();

    /**
     * Вывести информацию об очередном выполнении очередного этапа внутри бенчмарка.
     * @return Время выполнения этапа.
     */
    std::chrono::nanoseconds lap();

    /**
     * Вывести информацию об очередном выполнении очередного этапа внутри бенчмарка.
     * @param lapName Наименование этапа.
     * @return Время выполнения этапа.
     */
    std::chrono::nanoseconds lap(std::string_view lapName);

    void stop();
};

}

#endif //ENERGO_BENCHMARKTIMER_H
