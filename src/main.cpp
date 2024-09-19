#include <iostream>
#include <windows.h>
#include <conio.h>

#include "starter.h"

using namespace std;

void printLogo();

int main(int argc, char *argv[]) {
    hideCursor();
    printLogo();
    SYSTEM_POWER_STATUS sps;
    int batteryLifeBEG = 0;
    if (GetSystemPowerStatus(&sps)) {
        batteryLifeBEG = static_cast<double>(sps.BatteryLifePercent);
    }
    else {
        cerr << "Unable to retrieve battery status." << endl;
    }

    cout << "Current battery: ";
    if (batteryLifeBEG > 65) {
        cout << "\033[1;32m" << batteryLifeBEG << "%\033[0m\n\n";
    }
    else if (batteryLifeBEG > 35) {
        cout << "\033[1;33m" << batteryLifeBEG << "%\033[0m\n\n";
    }
    else {
        cout << "\033[1;31m" << batteryLifeBEG << "%\033[0m\n\n";
    }

    cpuTest();

    int batteryLifeEND = 0;
    if (GetSystemPowerStatus(&sps)) {
        batteryLifeEND = static_cast<double>(sps.BatteryLifePercent);
    }
    else {
        cerr << "Unable to retrieve battery status." << endl;
    }

    double batteryDif = batteryLifeBEG - batteryLifeEND;

    double lossPerMin = batteryDif / 10;

    double batteryLife = 100 / lossPerMin;

    system("cls");
    printLogo();
    cout << "Battery life at beginning: " << batteryLifeBEG << "%\n";
    cout << "Battery life at end: " << batteryLifeEND << "%\n";
    cout << "Battery lost per minute: " << lossPerMin << "%\n";
    cout << "Your battery will last from 100% to 0% for " << batteryLife << " minutes at the selected load." << endl;

    system("pause");
    return 0;
}

void printLogo() {
    cout << "\033[1;32m    ___           _                        \n";
    cout << "   /   \\_ __ __ _(_)_ __   __ _  __ _  ___ \n";
    cout << "  / /\\ / '__/ _` | | '_ \\ / _` |/ _` |/ _ \\ \n";
    cout << " / /_//| | | (_| | | | | | (_| | (_| |  __/ \n";
    cout << "/___,' |_|  \\__,_|_|_| |_|\\__,_|\\__, |\\___| \n";
    cout << "                                |___/      \033[0m\n";
}