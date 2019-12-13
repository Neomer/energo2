//
// Created by vinokurov on 11.12.2019.
//

#include <iostream>
#include "BenchmarkTimer.h"

using namespace std;
using namespace std::chrono;
using namespace energo::benchmark;
using namespace std::string_literals;


BenchmarkTimer::BenchmarkTimer(std::ostream &stream) :
    _startPoint{ high_resolution_clock::now() },
    _lap{high_resolution_clock::now()},
    _stream{ stream },
    _stopped{false}
{

}

BenchmarkTimer::BenchmarkTimer(string_view benchmarkName, ostream &stream)  :
    _startPoint{ high_resolution_clock::now() },
    _lap{high_resolution_clock::now()},
    _stream{ stream },
    _benchName{benchmarkName},
    _stopped{false}
{

}


BenchmarkTimer::BenchmarkTimer(std::string_view benchmarkName) :
        _startPoint{ high_resolution_clock::now() },
        _lap{high_resolution_clock::now()},
        _stream{ cout },
        _benchName{benchmarkName},
        _stopped{false}
{

}



BenchmarkTimer::~BenchmarkTimer() {
    stop();
}

nanoseconds BenchmarkTimer::lap() {
    return lap("");
}

nanoseconds BenchmarkTimer::lap(std::string_view lapName) {
    auto lapPoint = high_resolution_clock::now();
    auto duration = lapPoint - _lap;
    _stream << "Benchmark";
    if (_benchName != "") {
        _stream << "[" << _benchName << "] LAP";
    }
    if (lapName != "") {
        _stream << "[" << lapName << "]";
    }
    if (duration.count() > 3000000000) {
        _stream << ": " << duration_cast<seconds>(duration).count() << " s\n";
    } else if (duration.count() > 3000000) {
        _stream << ": " << duration_cast<milliseconds>(duration).count() << " ms\n";
    } else if (duration.count() > 3000) {
        _stream << ": " << duration_cast<microseconds>(duration).count() << " mcs\n";
    } else {
        _stream << ": " << duration.count() << " ns\n";
    }
    _lap = high_resolution_clock::now();
    return duration;
}

void BenchmarkTimer::stop() {
    if (_stopped) {
        return;
    }
    auto endPoint = high_resolution_clock::now();
    auto duration = endPoint - _startPoint;

    _stream << "Benchmark";
    if (_benchName != "") {
        _stream << "[" << _benchName << "]";
    }
    if (duration.count() > 3000000000) {
        _stream << ": " << duration_cast<seconds>(duration).count() << " s\n";
    } else if (duration.count() > 1000000000) {
        _stream << ": " << duration_cast<milliseconds>(duration).count() * 0.001 << " s\n";
    } else if (duration.count() > 3000000) {
        _stream << ": " << duration_cast<milliseconds>(duration).count() << " ms\n";
    } else if (duration.count() > 1000000) {
        _stream << ": " << duration_cast<microseconds>(duration).count() * 0.001 << " ms\n";
    } else if (duration.count() > 3000) {
        _stream << ": " << duration_cast<microseconds>(duration).count() << " mcs\n";
    } else if (duration.count() > 1000) {
        _stream << ": " << duration.count() * 0.001 << " mcs\n";
    } else {
        _stream << ": " << duration.count() << " ns\n";
    }
}
