#pragma once

#include <QXmlStreamWriter>
#include "living.hpp"

class b2Body;
class Scene;
class b2World;
class Simulation;

class Food : public Living
{
public:
    Food(int id, Simulation *simulation, Scene *scene, b2World *world, int x, int y, Food *parent, Type type);
    Food(int id, Simulation *simulation, Scene *scene, b2World * world, QXmlStreamReader & xml);
    ~Food();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void go(int step);
    virtual void buildPhenotype();
    virtual void save(QXmlStreamWriter & xml);
    void load(QXmlStreamReader &xml);
    static void reset();

    static int getCount();
    static int getEatenCount();
    static void setEatenCount(int i){eatenCount = i;}
    static float getGrowingSpeed(){return Food::growingSpeed;}
    static void setGrowingSpeed(float f){Food::growingSpeed = f;}

private:
    static int count;
    static int eatenCount;
    static float growingSpeed;
    float r;
    float g;
    float b;

};
