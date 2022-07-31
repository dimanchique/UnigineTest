#include <iostream>
#include "EntityManager.h"
#include <chrono>
#include "string"

void SetInputParams(int &num, int &field_size, float &fov, int &view_distance);
void LogDuration(std::chrono::high_resolution_clock::time_point t1, std::chrono::high_resolution_clock::time_point t2, const std::string& operation);
void LogVisibleUnits(EntityManager Manager);

int main() {
    EntityManager Manager;
    int NumOfEntities, FieldSize, ViewDistance; float FOV;
    std::chrono::high_resolution_clock::time_point start_time, stop_time;

    SetInputParams(NumOfEntities, FieldSize, FOV, ViewDistance);

    start_time = std::chrono::high_resolution_clock::now();
    Manager.CreateEntities(FieldSize, NumOfEntities, FOV, ViewDistance);
    stop_time = std::chrono::high_resolution_clock::now();
    LogDuration(start_time, stop_time, "creation");

    start_time = std::chrono::high_resolution_clock::now();
    Manager.CalculateVisibleUnits();
    stop_time = std::chrono::high_resolution_clock::now();
    LogDuration(start_time, stop_time, "calculation");

    LogVisibleUnits(Manager);

    return 0;
}

void SetInputParams(int &num, int &field_size, float &fov, int &view_distance)
{
    printf("Enter number of units: "); std::cin >> num; std::cout << std::endl;
    do {
        printf("Enter field size: "); std::cin >> field_size; std::cout << std::endl;
        if (field_size*field_size > num) break;
        printf("Can't fit %d units in field with size %dx%d. Try Again!\n", num, field_size, field_size);
    }
    while (true);

    printf("Enter FOV: "); std::cin >> fov; std::cout << std::endl;
    printf("Enter view distance: "); std::cin >> view_distance; std::cout << std::endl;
}

void LogDuration(std::chrono::high_resolution_clock::time_point t1, std::chrono::high_resolution_clock::time_point t2, const std::string& operation)
{
    std::chrono::duration<double, std::milli> ms_double = (t2 - t1)/1000;
    printf("Time taken by %s is: %f s\n", operation.c_str(), ms_double.count());
}

void LogVisibleUnits(EntityManager Manager)
{
    for (auto &Pair : Manager.EntityByID)
    {
        auto entity = Pair.second;
        printf("Unit %d see %d units: ", entity.ID, entity.VisibleEntitiesIDs.size());
        printf("{ ");
        for (auto ID : entity.VisibleEntitiesIDs) printf("%d ", ID);
        printf("}\n");
    }
}