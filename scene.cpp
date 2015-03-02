#include "scene.hpp"

#include "living.hpp"
#include "food.hpp"
#include "foosh.hpp"
#include "fire.hpp"
#include "constants.hpp"
#include "simulation.hpp"

#include <QDebug>

Scene::Scene(Simulation * simulation) : QGraphicsScene()
{
    setItemIndexMethod(QGraphicsScene::NoIndex);
    setSceneRect(simulation->getXmin()*2, simulation->getYmin()*2, simulation->getXmax()*4, simulation->getYmax()*4);
}

Scene::~Scene()
{

}

void Scene::advance()
{
    QList<QGraphicsItem*> aa = this->items();
    for(int i = aa.size() - 1 ; i >= 0 ; i--)
    {
        Living * living = static_cast<Living*>(aa[i]);
        living->go(1);
    }

    QGraphicsItem * item;
    foreach(item, items())
    {
        if(static_cast<Living*>(item)->isDead())
        {
            this->removeItem(item);
            delete item;
        }
    }
}

