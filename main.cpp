#include "UnitManager.h"
#include <chrono>
#include "string"

void LogDuration(std::chrono::high_resolution_clock::time_point t1, std::chrono::high_resolution_clock::time_point t2, const std::string& operation);

int main() {
    UnitManager Manager;
    int NumOfUnits, FieldSize, ViewDistance; float FOV;
    std::chrono::high_resolution_clock::time_point start_time, stop_time;

    FieldSize = 400;
    NumOfUnits = 10000;
    FOV = 130;
    ViewDistance = 5;

    start_time = std::chrono::high_resolution_clock::now();
    Manager.CreateUnits(FieldSize, NumOfUnits, FOV, ViewDistance);
    stop_time = std::chrono::high_resolution_clock::now();
    LogDuration(start_time, stop_time, "creation");

    start_time = std::chrono::high_resolution_clock::now();
    Manager.CalculateVisibleUnits();
    stop_time = std::chrono::high_resolution_clock::now();
    LogDuration(start_time, stop_time, "calculation");

    return 0;
}

void LogDuration(std::chrono::high_resolution_clock::time_point t1, std::chrono::high_resolution_clock::time_point t2, const std::string& operation)
{
    std::chrono::duration<double, std::milli> ms_double = (t2 - t1)/1000;
    printf("Time taken by %s is: %f s\n", operation.c_str(), ms_double.count());
}
