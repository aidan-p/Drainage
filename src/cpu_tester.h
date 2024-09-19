#ifndef CPU_TESTER_H
#define CPU_TESTER_H

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;
using namespace chrono;

void performTask(int loadPercentage, std::chrono::seconds duration);
void threadFunction(int loadPercentage, seconds duration);
void testCPUWithLoadAndThreads(int loadPercentage, std::chrono::seconds duration, unsigned int numThreads);

#endif // CPU_TESTER_H
