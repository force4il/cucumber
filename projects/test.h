#pragma once
#include "queue/queue.h"
#include "stack/stack.h"
#include <chrono>

using std::chrono::high_resolution_clock;
using std::chrono::time_point;
using std::chrono::nanoseconds;
using std::chrono::duration_cast;

// Вставка для структур на основе массива
template <typename ArrType>
long long array_timing_push(int N, ArrType& obj) {
    auto ArrType_push_start = high_resolution_clock::now();

    for (int i = 0; i < N; i++) obj.push(i);

    auto ArrType_push_end = high_resolution_clock::now();
    auto ArrType_push_res = duration_cast<nanoseconds>(ArrType_push_end-ArrType_push_start).count();

    return ArrType_push_res;
}

// Вставка для структур на основе списка
template <typename ListType>
long long list_timing_push(int N, ListType& obj) {
    auto ListType_push_start = high_resolution_clock::now();

    for (int i = 0; i < N; i++) obj.push(new node(i));

    auto ListType_push_end = high_resolution_clock::now();
    auto ListType_push_res = duration_cast<nanoseconds>(ListType_push_end-ListType_push_start).count();

    return ListType_push_res;
}

// Удаление для структур на основе массива
template <typename ArrType>
long long array_timing_pop(int N, ArrType& obj) {
    auto ArrType_pop_start = high_resolution_clock::now();

    for (int i = 0; i < N; i++) obj.pop();

    auto ArrType_pop_end = high_resolution_clock::now();
    auto ArrType_pop_res = duration_cast<nanoseconds>(ArrType_pop_end-ArrType_pop_start).count();

    return ArrType_pop_res;
}

// Вставка для структур на основе списка
template <typename ListType>
long long list_timing_pop(int N, ListType& obj) {
    auto ListType_pop_start = high_resolution_clock::now();

    for (int i = 0; i < N; i++) obj.pop();

    auto ListType_pop_end = high_resolution_clock::now();
    auto ListType_pop_res = duration_cast<nanoseconds>(ListType_pop_end-ListType_pop_start).count();

    return ListType_pop_res;
}
