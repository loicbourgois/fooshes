#ifndef FOOSH_H
#define FOOSH_H

#include "living.h"
#include "eye.h"

#include "brain.h"

class Foosh : public Living
{
public:
    Foosh(int id, Simulation * simulation, Scene *scene, b2World * world, int x, int y, Foosh *parent, Type type);
    Foosh(int id, Simulation *simulation, Scene *scene, b2World *world, QXmlStreamReader &xml);
    ~Foosh();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);
    void go(int step);
    virtual void buildPhenotype();
    void save(QXmlStreamWriter &xml);
    void load(QXmlStreamReader &xml);

    int getSpeciesAge();
    static void reset();
    static int getCount();
    static int getDeaths();
    static void setDeathCount(int i){deaths = i;}

    static float getSpeedMax(){return Foosh::globalSpeedMax;}
    static void setSpeedMax(float f){Foosh::globalSpeedMax = f;}
    static float getAngularSpeedMax(){return Foosh::globalAngularSpeedMax;}
    static void setAngularSpeedMax(float f){Foosh::globalAngularSpeedMax = f;}

    static float getAgingSpeed(){return Foosh::agingSpeed;}
    static void setAgingSpeed(float f){Foosh::agingSpeed = f;}

    static float getDigestionMax(){return Foosh::digestionMax;}
    static void setDigestionMax(float f){Foosh::digestionMax = f;}

private:
    std::vector<Eye*> eyes;
    static int count;
    static int olderAge;
    static int deaths;
    static float globalSpeedMax;
    static float globalAngularSpeedMax;
    static float agingSpeed;
    static float digestionMax;
    static int reflexionTime;
    static Foosh * olderFoosh;
    float speed;
    float speedMax;
    float angularSpeed;
    float angularSpeedMax;
    int age;
    int speciesAge;
    Brain * brain;

};

#endif // FOOSH_H
