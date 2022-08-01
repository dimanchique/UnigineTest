#include "UnitManager.h"

uint32_t UnitManager::UnitsCount = 0;

void UnitManager::CreateUnits(int FieldSize, uint32_t NumOfUnits, float FOV, int ViewDistance) {
    int size = FieldSize/2;
    CreateClusters(size, ViewDistance);
    for (int i = 0; i < NumOfUnits; ++i) {
        Vector2 EntityPosition;
        GenerateNotOccupiedLocation(size, EntityPosition);
        Vector2 EntityRotation = Vector2::GetRandomRotatedVector();
        InitializeUnits(EntityPosition, EntityRotation, FOV, ViewDistance);
    }
}

bool UnitManager::FieldPointIsOccupied(Vector2 Position) {
    return UnitsIDsByLocation.find((int)Position.X) != UnitsIDsByLocation.end()
           &&
           UnitsIDsByLocation.at((int)Position.X).find((int)Position.Y) != UnitsIDsByLocation.at((int)Position.X).end();
}

Vector2 UnitManager::GetClusterForPosition(Vector2 Position, int ClusterSize) {
    int X_Cluster = Position.X > 0 ?
                    ClusterSize * ((int) Position.X / ClusterSize) :
                    ClusterSize * (((int) Position.X / ClusterSize) - 1);
    int Y_Cluster = Position.Y > 0 ?
                    ClusterSize * ((int) Position.Y / ClusterSize) :
                    ClusterSize * (((int) Position.Y / ClusterSize) - 1);
    return Vector2(X_Cluster, Y_Cluster);
}

void UnitManager::CreateClusters(uint32_t StartPosition, int ClusterSize) {
    for (int i = -StartPosition; i < (int) StartPosition; i += ClusterSize) {
        for (int j = -StartPosition; j < (int) StartPosition; j += ClusterSize) {
            UnitsIDsByCluster[i][j];
        }
    }
}

void UnitManager::GenerateNotOccupiedLocation(int Band, Vector2 &Position) {
    do {
        Position = Vector2(std::experimental::randint(-Band, Band - 1),
                           std::experimental::randint(-Band, Band - 1));
    } while (FieldPointIsOccupied(Position));
}

void UnitManager::InitializeUnits(Vector2 position, Vector2 rotation, float fov, int view_distance) {
    Unit entity(position, rotation, fov, view_distance, UnitsCount);
    UnitsByID[entity.ID] = entity;
    UnitsIDsByLocation[(int)entity.Position.X][(int)entity.Position.Y] = entity.ID;
    auto EntityCluster = GetClusterForPosition(entity.Position, entity.ViewDistance);
    UnitsIDsByCluster[(int)EntityCluster.X][(int)EntityCluster.Y].push_back(UnitsCount++);
}

void UnitManager::CalculateVisibleUnits() {
    for (auto &Pair : UnitsByID) {
        auto &RootEntity = Pair.second;
        auto VisibleClusters = RayTraceSector(RootEntity);
        for (auto Cluster : VisibleClusters)
        {
            for (auto TargetEntity : GetUnitsByIDs(GetUnitsInCluster(Cluster)))
            {
                if (RootEntity.ID != TargetEntity.ID)
                    if (RootEntity.CanSee(TargetEntity))
                        RootEntity.VisibleUnitsIDs.push_back(TargetEntity.ID);
            }
        }
    }
}

std::vector<Vector2> UnitManager::RayTraceSector(Unit &unit) {
    std::vector<Vector2> ClustersAroundUnit;
    float AngleStep = unit.FOV / 8;
    for (int i = 0; i < 8; ++i) {
        Vector2 TraceVector = unit.ViewDirection;
        TraceVector*=unit.ViewDistance;
        TraceVector.rotate(i * AngleStep);
        TraceVector+=unit.Position;
        auto TracedCluster = GetClusterForPosition(TraceVector, unit.ViewDistance);
        bool ClusterAlreadyTraced = false;
        for (auto Cluster : ClustersAroundUnit)
        {
            if (Cluster == TracedCluster) {
                ClusterAlreadyTraced = true;
                break;
            }
        }
        if (!ClusterAlreadyTraced)
            ClustersAroundUnit.push_back(TracedCluster);
    }
    return ClustersAroundUnit;
}
