#ifndef FIRE_H
#define FIRE_H

#include "living.hpp"



class Fire : public Living
{
public:
    Fire(int id, Simulation * simulation, Scene *scene, b2World * world, int x, int y, Fire *parent, Type type);
    Fire(int id, Simulation *simulation, Scene *scene, b2World * world, QXmlStreamReader & xml);
    void go(int step);
    ~Fire();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual void buildPhenotype();
    static void resetCounts();
    void save(QXmlStreamWriter &xml);
    void load(QXmlStreamReader &xml);
private:
    static int count;
};

#endif // FIRE_H
