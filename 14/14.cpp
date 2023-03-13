#include <Windows.h>
#include <iostream>

#include "Queue.h"

using namespace std;

const int N = 25;

struct Day {
    int TimeEve = NULL;
    int TimeMor = NULL;
    int TimeAft = NULL;
    int BusStop = NULL;
};

void EnterData(Day& passTime, Day& busTime) {
    cout << "Input time evening, morning, afternoon\n";
    cin >> passTime.TimeEve >> passTime.TimeMor >> passTime.TimeAft;

    cout << "Input time evening, morning, afternoon\n";
    cin >> busTime.TimeEve >> busTime.TimeMor >> busTime.TimeAft;

    cout << "Input bus station 1 - final, 0 - next station\n";
    cin >> busTime.BusStop;
}

int AverageTime(int passTimeAf, int bussTimeAf, int mode) {
    int maxSizeBus = NULL; 

    if (mode == 0) maxSizeBus = 6;
    else if (mode == 1) maxSizeBus = 4;
    else if (mode == 2) maxSizeBus = 5;

    int maxTimesRepeat = 1000;
    srand(time(NULL));
    Queue passengers(N); 
    int averageTimeStay = 0;
    int averageTimesSpent = 0;

    int timeSpent = 0;
    int countBusSpent = 0;

    int a = 0;
    while (maxTimesRepeat != 0) {
        maxTimesRepeat--;

        for (int i = 0; i < bussTimeAf / passTimeAf; i++) {
            passengers.add(i + 1);
        }
 
        if (passengers.isFull())
            return -1;


        timeSpent += bussTimeAf;

        countBusSpent++;

        int busSeats = rand() % maxSizeBus + 1;

        for (int i = 0; i < busSeats; i++) {
            passengers.extract();
        }

        if (passengers.isEmpty()) {
            averageTimeStay += timeSpent / countBusSpent;
            averageTimesSpent++;
            timeSpent = 0;
            countBusSpent = 0;
        }

    }
    return averageTimeStay / averageTimesSpent;
}

int OptimumTime(int passTime, int maxSizeBus) {
 
    return passTime * (maxSizeBus * maxSizeBus);
}

int main()
{
    Day busTime;
    Day passTime;

    EnterData(passTime, busTime);

    int avTimeAf = AverageTime(passTime.TimeAft, busTime.TimeAft, 0);
    int avTimeEv = AverageTime(passTime.TimeEve, busTime.TimeEve, 2);
    int avTimeMo = AverageTime(passTime.TimeMor, busTime.TimeMor, 1);

    cout << "Afternoon\n\n";
    if (avTimeAf != -1)
        cout << " time during " << avTimeAf << endl;
    else
        cout << "bus fulled\n";
    cout << "Best time - " << OptimumTime(passTime.TimeAft, 4) << endl;

    cout << "\nEvening\n\n";
    if (avTimeEv != -1)
        cout << " time during " << avTimeEv << endl;
    else
        cout << "bus fulled\n";
    cout << "Best time - " << OptimumTime(passTime.TimeEve, 3) << endl;

    cout << "\nMorning\n\n";
    if (avTimeMo != -1)
        cout << " time during " << avTimeMo << endl;
    else
        cout << "bus fulled\n";
    cout << "Best time - " << OptimumTime(passTime.TimeMor, 2) << endl;



}