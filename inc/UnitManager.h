#pragma once
#include "Unit.h"
#include "Vector2.h"
#include "vector"
#include "unordered_map"

class UnitManager {
    static uint32_t UnitsCount;
public:
    UnitManager() = default;
    void CreateUnits(int FieldSize, uint32_t NumOfUnits, float FOV, int ViewDistance);
    void CalculateVisibleUnits();
    std::unordered_map<uint32_t, Unit> UnitsByID;

private:
    std::unordered_map<int, std::unordered_map<int, std::vector<uint32_t>>> UnitsIDsByCluster;
    std::unordered_map<int, std::unordered_map<int,uint32_t>> UnitsIDsByLocation;

    void InitializeUnits(Vector2 &position, Vector2 &rotation, float &fov, int &view_distance);
    void GenerateNotOccupiedLocation(int &Band, Vector2 &Position);
    bool FieldPointIsOccupied(Vector2 &Position);
    static void GetClusterForPosition(Vector2 &Cluster, Vector2 &Position, int &ClusterSize);
    static void RayTraceNearClusters(Unit &unit, std::vector<Vector2> &ClustersAroundUnit);

    Unit GetUnitByID(uint32_t ID) { return UnitsByID[ID]; }
    void GetUnitsIDsInCluster(std::vector<uint32_t> &IDs, Vector2 &Cluster) {
        IDs = UnitsIDsByCluster[(int)Cluster.X][(int)Cluster.Y];
    }
    void GetUnitsByIDs(std::vector<Unit> &Units, std::vector<uint32_t> &IDs) {
        Units.clear();
        for (auto &ID : IDs)
            Units.push_back(GetUnitByID(ID));
    }
};
