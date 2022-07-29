#include <iostream>
#include "EntityManager.h"

int main() {
    EntityManager Manager;
    int NumOfEntities, FieldSize, FOV, ViewDistance;
    std::cout << "Enter number of entities: ";
    std::cin >> NumOfEntities;
    std::cout << std::endl;

    bool ValueIsOkay;
    do {
        std::cout << "Enter field size: ";
        std::cin >> FieldSize;
        std::cout << std::endl;
        ValueIsOkay = pow(FieldSize, 4) > NumOfEntities; // 4 is because we use range -FieldSize -> FieldSize instead of 0 -> FieldSize
        if (!ValueIsOkay)
            std::cout << "Can't fit " << NumOfEntities << " entities in field with size " << FieldSize << "x" << FieldSize << ". Try Again" << std::endl;
    }
    while (!ValueIsOkay);

    std::cout << "Enter FOV: ";
    std::cin >> FOV;
    std::cout << std::endl;
    std::cout << "Enter view distance: ";
    std::cin >> ViewDistance;
    std::cout << std::endl;

    Manager.CreateEntities(FieldSize, NumOfEntities, FOV, ViewDistance);
    Manager.CalculateVisibleUnits();

    for (auto Pair : Manager.EntityByID)
    {
        auto entity = Pair.second;
        std::cout << "Entity " << entity.ID << " see " << entity.VisibleEntitiesIDs.size() << " entities ";
        std::cout << "{ ";
        for (auto ID : entity.VisibleEntitiesIDs)
            std::cout << ID << " ";
        std::cout << "}" << std::endl;
    }
    return 0;
}
