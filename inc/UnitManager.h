#pragma once
#include "Unit.h"
#include "Vector2.h"
#include "vector"
#include "map"

class UnitManager {
    static uint32_t UnitsCount;
public:
    UnitManager() = default;
    void CreateUnits(int FieldSize, uint32_t NumOfUnits, float FOV, int ViewDistance);
    void CalculateVisibleUnits();
    std::map<uint32_t, Unit> UnitsByID;

private:
    std::map<int, std::map<int, std::vector<uint32_t>>> UnitsIDsByCluster;
    std::map<int, std::map<int,uint32_t>> UnitsIDsByLocation;

    void InitializeUnits(Vector2 &position, Vector2 &rotation, float &fov, int &view_distance);
    void CreateClusters(uint32_t StartPosition, int ClusterSize);
    void GenerateNotOccupiedLocation(int Band, Vector2 &Position);
    bool FieldPointIsOccupied(Vector2 &Position);
    static Vector2 GetClusterForPosition(Vector2 &Position, int &ClusterSize);
    std::vector<Vector2> RayTraceSector(Unit &unit);

    Unit GetUnitByID(uint32_t ID) { return UnitsByID[ID]; }
    std::vector<uint32_t>& GetUnitsInCluster(Vector2 &Cluster) {
        return UnitsIDsByCluster[(int)Cluster.X][(int)Cluster.Y];
    }
    std::vector<Unit> GetUnitsByIDs(std::vector<uint32_t> &IDs) {
        std::vector<Unit> units;
        for (auto &ID : IDs)
        {
            units.push_back(GetUnitByID(ID));
        }
        return units;
    }

};
