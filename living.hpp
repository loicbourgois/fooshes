#ifndef LIVING_H
#define LIVING_H



#include <Box2D/Box2D.h>
#include "my_query_callback.hpp"

#include <QXmlStreamWriter>


#include <QGraphicsItem>
#include <Qvariant>

class b2Body;
class Scene;
class b2World;
class Simulation;



class Living : public QGraphicsItem
{
public:
    enum class Type : int
    {
        FIRE = 0,
        FOOD = 10,
        FOOSH = 20
    };
    Living(int  id, Simulation * simulation, Scene *scene, b2World * world, int x, int y, Living * parent, Type type, int DNAsize, float ratio1, float ratio2, float ratio3);
    virtual ~Living();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int step);

    virtual void buildPhenotype() = 0 ;
    virtual void go(int phase);

    void setRandomDNA();
    void setGene(int id, float value);
    void setCoord(float x, float y);

    bool isDead(){return dead;}
    void kill(){dead = true;}

    float getGene(int geneId);
    Type getType();
    QColor getColor();
    float getEnergy();
    float getNextCharacter(float min, float max);
    float getX();
    float getY();

    virtual void save(QXmlStreamWriter &xml);

protected:
    void mutateDNA();
    float getCharacter(unsigned int geneId, float min, float max);

    Simulation * simulation;
    Scene * scene;
    b2Body * body;
    QPolygon polygon;
    int radius;
    QColor color;

    int DNAsize;
    std::vector<float> DNA;
    float ratio1;
    float ratio2;
    float ratio3;
    int idCharacter;

    int id;
    Type type;
    float energy;
    bool dead;

private:

};

#endif // LIVING_H
