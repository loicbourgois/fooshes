#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

class Simulation;

class Scene : public QGraphicsScene
{
public:
    Scene(Simulation * simulation);
    ~Scene();
    void advance();
};

#endif // SCENE_H
