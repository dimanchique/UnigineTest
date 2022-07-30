#include <iostream>
#include "EntityManager.h"
#include <chrono>

int main() {
    EntityManager Manager;
    int NumOfEntities, FieldSize, FOV, ViewDistance;

    std::cout << "Enter number of entities: "; std::cin >> NumOfEntities; std::cout << std::endl;

    do {
        std::cout << "Enter field size: "; std::cin >> FieldSize; std::cout << std::endl;
        if (FieldSize*FieldSize > NumOfEntities)
            break;
        std::cout << "Can't fit " << NumOfEntities << " entities in field with size " << FieldSize << "x" << FieldSize << ". Try Again" << std::endl;
    }
    while (true);

    std::cout << "Enter FOV: "; std::cin >> FOV; std::cout << std::endl;
    std::cout << "Enter view distance: "; std::cin >> ViewDistance; std::cout << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    Manager.CreateEntities(FieldSize, NumOfEntities, FOV, ViewDistance);
    auto end = std::chrono::high_resolution_clock::now();
    double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;
    std::cout << "Time taken by creation is : " << std::fixed << time_taken << " sec " << std::endl;

    start = std::chrono::high_resolution_clock::now();
    Manager.CalculateVisibleUnits();
    end = std::chrono::high_resolution_clock::now();
    time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    time_taken *= 1e-9;
    std::cout << "Time taken by calculation is : " << std::fixed << time_taken << " sec " << std::endl;

//    for (auto Pair : Manager.EntityByID)
//    {
//        auto entity = Pair.second;
//        printf("Entity %d see %d entities: ", entity.ID, entity.VisibleEntitiesIDs.size());
//        std::cout << "{ ";
//        for (auto ID : entity.VisibleEntitiesIDs)
//            std::cout << ID << " ";
//        std::cout << "}" << std::endl;
//    }
    return 0;
}
