#pragma once

#include <Box2D/Box2D.h>
#include <QDebug>

class MyQueryCallback : public b2QueryCallback {
public:
    std::vector<b2Body*> foundBodies;

    bool ReportFixture(b2Fixture * fixture) {
        foundBodies.push_back( fixture->GetBody() );
        return true;//keep going to find all fixtures in the query area
    }
};

class RayCastClosestCallback : public b2RayCastCallback
{
public:
    RayCastClosestCallback()
    {
        hit = false;
    }
    float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
    {
        hit = true;
        this->point = point;
        this->normal = normal;
        body = fixture->GetBody();
        return fraction;
    }
    bool hit;
    b2Vec2 point;
    b2Vec2 normal;
    b2Body * body;
};
