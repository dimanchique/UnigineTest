#include "UnitManager.h"

uint32_t UnitManager::UnitsCount = 0;

void UnitManager::CreateUnits(int FieldSize, uint32_t NumOfUnits, float FOV, int ViewDistance) {
    int size = FieldSize/2;
    Vector2 UnitPosition;
    Vector2 UnitRotation;
    for (int i = 0; i < NumOfUnits; ++i) {
        Vector2::GetRandomRotatedVector(UnitRotation);
        GenerateNotOccupiedLocation(size, UnitPosition);
        InitializeUnits(UnitPosition, UnitRotation, FOV, ViewDistance);
    }
}

bool UnitManager::FieldPointIsOccupied(Vector2 &Position) {
    return UnitsIDsByLocation.find((int)Position.X) != UnitsIDsByLocation.end()
           &&
           UnitsIDsByLocation.at((int)Position.X).find((int)Position.Y) != UnitsIDsByLocation.at((int)Position.X).end();
}

void UnitManager::GetClusterForPosition(Vector2 &Cluster, Vector2 &Position, int &ClusterSize) {
    int X_Cluster = Position.X > 0 ?
                    ClusterSize * ((int) Position.X / ClusterSize) :
                    ClusterSize * (((int) Position.X / ClusterSize) - 1);
    int Y_Cluster = Position.Y > 0 ?
                    ClusterSize * ((int) Position.Y / ClusterSize) :
                    ClusterSize * (((int) Position.Y / ClusterSize) - 1);
    Cluster = Vector2((float)X_Cluster, (float)Y_Cluster);
}

void UnitManager::GenerateNotOccupiedLocation(int &Band, Vector2 &Position) {
    do { Vector2::GetRandomVector(Band, Position); } while (FieldPointIsOccupied(Position));
}

void UnitManager::InitializeUnits(Vector2 &position, Vector2 &rotation, float &fov, int &view_distance) {
    Unit unit(position, rotation, fov, view_distance, UnitsCount);
    UnitsByID[unit.ID] = unit;
    UnitsIDsByLocation[(int)unit.Position.X][(int)unit.Position.Y] = unit.ID;
    Vector2 UnitCluster;
    GetClusterForPosition(UnitCluster, unit.Position, unit.ViewDistance);
    UnitsIDsByCluster[(int)UnitCluster.X][(int)UnitCluster.Y].emplace_back(UnitsCount++);
}

void UnitManager::CalculateVisibleUnits() {
    std::vector<Vector2> VisibleClusters;
    std::vector<Unit> Units;
    std::vector<uint32_t> IDs;
    for (auto &[UnitID, RootUnit]: UnitsByID) {
        RayTraceNearClusters(RootUnit, VisibleClusters);
        for (auto &Cluster: VisibleClusters) {
            GetUnitsIDsInCluster(IDs, Cluster);
            GetUnitsByIDs(Units, IDs);
            for (auto &TargetUnit: Units) {
                if (RootUnit.ID != TargetUnit.ID)
                    if (RootUnit.CanSee(TargetUnit))
                        RootUnit.VisibleUnitsIDs.emplace_back(TargetUnit.ID);
            }
        }
    }
}

void UnitManager::RayTraceNearClusters(Unit &unit, std::vector<Vector2> &ClustersAroundUnit) {
    ClustersAroundUnit.clear();
    Vector2 TracedCluster;
    for (auto &Trace : unit.RayTraces) {
        GetClusterForPosition(TracedCluster, Trace, unit.ViewDistance);
        bool ClusterAlreadyTraced = false;
        for (auto &Cluster : ClustersAroundUnit)
        {
            if (Cluster == TracedCluster) {
                ClusterAlreadyTraced = true;
                break;
            }
        }
        if (!ClusterAlreadyTraced)
            ClustersAroundUnit.emplace_back(TracedCluster);
    }
}
