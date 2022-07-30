#pragma once
#include "Entity.h"
#include "Vector2.h"
#include "vector"
#include "map"

class EntityManager {
    static uint32_t EntityCount;
public:
    EntityManager() = default;
    void CreateEntities(int FieldSize, uint32_t NumOfEntities, float FOV, int ViewDistance);
    void CalculateVisibleUnits();
    std::map<uint32_t, Entity> EntityByID;

private:
    std::map<int, std::map<int, std::vector<uint32_t>>> ClusterOfEntitiesIDs;
    std::map<int, std::map<int,uint32_t>> EntitiyIDByLocation;

    void InitializeEntity(Vector2 position, Vector2 rotation, float fov, int view_distance);
    void CreateClusters(uint32_t StartPosition, int ClusterSize);
    void GenerateNotOccupiedLocation(int Band, Vector2 &Position);
    bool FieldPointIsOccupied(Vector2 Position);
    static Vector2 GetClusterForPosition(Vector2 Position, int ClusterSize);
    std::vector<Vector2> RayTraceSector(Entity entity);

    Entity GetEntityByID(uint32_t ID) { return EntityByID[ID]; }
    std::vector<uint32_t> GetEntitiesIDsByCluster(Vector2 Cluster) {
        return ClusterOfEntitiesIDs[(int)Cluster.X][(int)Cluster.Y];
    }
    std::vector<Entity> GetEntitiesByIDs(std::vector<uint32_t> IDs) {
        std::vector<Entity> entities;
        for (auto ID : IDs)
        {
            entities.push_back(GetEntityByID(ID));
        }
        return entities;
    }

};
