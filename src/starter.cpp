#include <iostream>
#include <chrono>
#include <string>
#include <unistd.h>
#include <thread>
#include <conio.h>
#include <windows.h>

#include "starter.h"
#include "cpu_tester.h"

using namespace std;
using namespace chrono;

void setCursorPosition(int x, int y) {
    COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE; // Hide cursor
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void showCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = TRUE; // Show cursor
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

string getLoadingBar(int counter, int duration) {
	int totalSpots = 50;
	int spotsFilled = counter * totalSpots / duration;
	string loadingBar;
	
	const string GREENTEXT = "\033[32m";
	const string GREENBACK = "\033[42m";
	const string WHITEBACK = "\033[47m";
	const string RESET = "\033[0m";

	for (int i = 0; i < totalSpots; i++) {
		if (i < spotsFilled) {
			loadingBar += GREENTEXT + GREENBACK + '\\' + RESET;
		}
		else {
			loadingBar += WHITEBACK + '/' + RESET;
		}
	}

	return loadingBar;
}

void cpuTest() {
	char load = 0;
	int duration = 600; // Normally set to 600 (10 minute tests, might need to increase for more accuracy)

	cout << "Please note: this is a very basic test that will stress your cores for 10 minutes.\n";
	cout << "The purpose of this test is to estimate how long a battery will last at different load levels.\n";
	cout << "Do not use this to test stability.\n\n\n";

	// LOAD
	cout << "Amount of Load:\n";
	cout << "	1. \033[33mLow\033[0m\n";
	cout << "	2. \033[38;5;214mMedium\033[0m\n";
	cout << "	3. \033[1;31mHigh\033[0m\n";
    while (true) {
        while (!_kbhit()) {
            // Do nothing, just wait
        }

        load = _getch();  // Get the pressed key
		if (load == '1' || load == '2' || load == '3') break;
    }

	// START MONITORING CPU
	bool isMonitoring = true;
	int counter = 0;
	string bar;
	system("cls");
	thread monitorThread([&]() {
		while (isMonitoring) {
			auto start = std::chrono::steady_clock::now(); // Capture time code block starts execution

			setCursorPosition(0, 1); // Move cursor to a specific line
			cout << "Running test at ";
			if (load == '1') {
				cout << "\033[33mlow \033[0m";
			}
			else if (load == '2') {
				cout << "\033[38;5;214mmedium \033[0m";
			}
			else if (load == '3') {
				cout << "\033[1;31mhigh \033[0m";
			}
			cout << "load:\n";
			counter++;
			bar = getLoadingBar(counter, duration);
			cout << bar << endl;

			// End time for code block
			auto end = std::chrono::steady_clock::now();
			std::chrono::duration<double> elapsed_seconds = end - start;
			std::chrono::duration<double> sleep_duration = std::chrono::seconds(1) - elapsed_seconds;

			// ==> Used to just sleep for 1 second, but this was inaccurate
			// ==> We now calculate how long it took to run code block and sleep accordingly
			if (sleep_duration > std::chrono::duration<double>(0)) {
				std::this_thread::sleep_for(sleep_duration);
			}
		}
	});

	// Run test
	if (load == '1') {			// ==> Single threaded with lower simulated load
		testCPUWithLoadAndThreads(25, seconds(duration), 1);
	}
	else if (load == '2') {		// ==> Half of the total threads with medium  simulated load
		testCPUWithLoadAndThreads(50, seconds(duration), thread::hardware_concurrency() / 2);
	}
	else if (load == '3') {		// ==> Every thread with max simulated load
		testCPUWithLoadAndThreads(100, seconds(duration), thread::hardware_concurrency());
	}

	// Stop monitoring
	isMonitoring = false;
	monitorThread.join(); // Wait for monitor thread to finish
}