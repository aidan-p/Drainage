#ifndef STARTER_H
#define STARTER_H

#include <iostream>
#include <chrono>
#include <string>
#include <unistd.h>
#include <thread>
#include <conio.h>
#include <windows.h>

#include "cpu_tester.h"

using namespace std;
using namespace chrono;

void setCursorPosition(int x, int y);
string getLoadingBar(int counter, int duration);
void cpuTest();
void hideCursor();
void showCursor();

#endif // STARTER_H