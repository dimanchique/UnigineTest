#pragma once

#include "Vector2.h"

struct Entity {
public:
    Entity()
    {
        Position = Vector2();
        ViewDirection = Vector2();
        FOV = 0;
        ViewDistance = 0;
        ID = 0;
    }
    Entity(Vector2 position, Vector2 rotation, float fov, int view_distance, uint32_t id){
        Position = position;
        ViewDirection = rotation;
        FOV = fov;
        ViewDistance = view_distance;
        ID = id;
        ViewDirection.normalize();
    }

    bool CanSee(Entity other)
    {
        float Distance = Vector2::distance(Position, other.Position);
        if (Distance > ViewDistance)
            return false;
        Vector2 TargetDirection = other.Position - Position;
        TargetDirection.normalize();
        float Angle = acos(Vector2::dot(ViewDirection, TargetDirection)) * 57.295779513f;
        if (Angle > FOV/2)
            return false;
        return true;
    }

    Vector2 Position;
    Vector2 ViewDirection;
    float FOV;
    int ViewDistance;
    std::vector<uint32_t> VisibleEntitiesIDs;
    uint32_t ID;
};
