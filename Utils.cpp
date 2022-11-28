//
// Created by MikoG on 26.11.2022.
//
#include "peer-to-peer-net.cpp"

void Utils::delay(uint128_t Microseconds) {
    clock_t goal = Microseconds + clock();
    while (goal > clock());
}

