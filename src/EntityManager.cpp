#include "EntityManager.h"

uint32_t EntityManager::EntityCount = 0;

void EntityManager::CreateEntities(int FieldSize, uint32_t NumOfEntities, float FOV, int ViewDistance) {
    int size = FieldSize/2;
    CreateClusters(size, ViewDistance);
    for (int i = 0; i < NumOfEntities; ++i) {
        Vector2 EntityPosition;
        GenerateNotOccupiedLocation(size, EntityPosition);
        Vector2 EntityRotation = Vector2::GetRandomRotatedVector();
        InitializeEntity(EntityPosition, EntityRotation, FOV, ViewDistance);
    }
}

bool EntityManager::FieldPointIsOccupied(Vector2 Position) {
    return EntitiyIDByLocation.find((int)Position.X) != EntitiyIDByLocation.end()
           &&
           EntitiyIDByLocation.at((int)Position.X).find((int)Position.Y) != EntitiyIDByLocation.at((int)Position.X).end();
}

Vector2 EntityManager::GetClusterForPosition(Vector2 Position, int ClusterSize) {
    int X_Cluster = Position.X > 0 ?
                    ClusterSize * ((int) Position.X / ClusterSize) :
                    ClusterSize * (((int) Position.X / ClusterSize) - 1);
    int Y_Cluster = Position.Y > 0 ?
                    ClusterSize * ((int) Position.Y / ClusterSize) :
                    ClusterSize * (((int) Position.Y / ClusterSize) - 1);
    return Vector2(X_Cluster, Y_Cluster);
}

void EntityManager::CreateClusters(uint32_t StartPosition, int ClusterSize) {
    for (int i = -StartPosition; i < (int) StartPosition; i += ClusterSize) {
        for (int j = -StartPosition; j < (int) StartPosition; j += ClusterSize) {
            ClusterOfEntitiesIDs[i][j];
        }
    }
}

void EntityManager::GenerateNotOccupiedLocation(int Band, Vector2 &Position) {
    do {
        Position = Vector2(std::experimental::randint(-Band, Band - 1),
                           std::experimental::randint(-Band, Band - 1));
    } while (FieldPointIsOccupied(Position));
}

void EntityManager::InitializeEntity(Vector2 position, Vector2 rotation, float fov, int view_distance) {
    Entity entity(position, rotation, fov, view_distance, EntityCount);
    EntityByID[entity.ID] = entity;
    EntitiyIDByLocation[(int)entity.Position.X][(int)entity.Position.Y] = entity.ID;
    auto EntityCluster = GetClusterForPosition(entity.Position, entity.ViewDistance);
    ClusterOfEntitiesIDs[(int)EntityCluster.X][(int)EntityCluster.Y].push_back(EntityCount++);
}

void EntityManager::CalculateVisibleUnits() {
    for (auto &Pair : EntityByID) {
        auto &RootEntity = Pair.second;
        auto VisibleClusters = RayTraceSector(RootEntity);
        for (auto Cluster : VisibleClusters)
        {
            for (auto TargetEntity : GetEntitiesByIDs(GetEntitiesIDsByCluster(Cluster)))
            {
                if (RootEntity.ID != TargetEntity.ID)
                    if (RootEntity.CanSee(TargetEntity))
                        RootEntity.VisibleEntitiesIDs.push_back(TargetEntity.ID);
            }
        }
    }
}

std::vector<Vector2> EntityManager::RayTraceSector(Entity &unit) {
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
