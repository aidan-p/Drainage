#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

#include "cpu_tester.h"

using namespace std;
using namespace chrono;

void performTask(int loadPercentage, seconds duration) {
	auto start = high_resolution_clock::now();
	auto end = start + duration;

	auto workTime = milliseconds(loadPercentage);
	auto sleepTime = milliseconds(100 - loadPercentage);

	while (high_resolution_clock::now() < end) {
		auto loopStart = high_resolution_clock::now();

		while (high_resolution_clock::now() - loopStart < workTime) {
			// ==> SIMPLE PRIMALITY TEST

			// Generates random number that we will be using to find whether it is prime or not
			srand(static_cast<unsigned>(time(NULL)));
			unsigned int num = rand();
			bool numFound = false;

			// Vector to store numbers that we have tested
			vector<unsigned int> numberList;

			while (!numFound) {
				while (true) {
					unsigned int randomNumber = rand() % (num - 1) + 1;		// ==> TESTING NUMBER

					bool inList = false;
					for (unsigned int i = 0; i < numberList.size(); i++) {
						if (numberList[i] == randomNumber) {
							inList = true;
							break;
						}
					}

					if (!inList) {
						numberList.push_back(randomNumber);
						break;
					}

					if (numberList.size() == num - 1) {
						break;
					}
				}

				// If num is divisible by the most recent element, then it is not prime
				if (num % numberList.back() == 0) {
					numFound = true;
				}
			}
		}

		// Sleep for rest of cycle
		this_thread::sleep_for(sleepTime);
	}
}

void threadFunction(int loadPercentage, seconds duration) {
	performTask(loadPercentage, duration);
}

void testCPUWithLoadAndThreads(int loadPercentage, seconds duration, unsigned int numThreads) {
	// Get number of hardware threads/cores
	cout << "Running test on " << numThreads << " threads.\n";

	// Create vector of threads
	vector<thread> threads;
	for (unsigned int i = 0; i < numThreads; i++) {
		threads.emplace_back(thread(threadFunction, loadPercentage, duration));
	}

	// Join threads
	for (auto& thread: threads) {
		thread.join();
	}
}