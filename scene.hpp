#pragma once

#include <QGraphicsScene>

class Simulation;

class Scene : public QGraphicsScene
{
public:
    Scene(Simulation * simulation);
    ~Scene();
    void advance();
};
