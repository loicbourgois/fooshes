#include "living.hpp"

#include "scene.hpp"
#include <Box2D/Box2D.h>
#include <QXmlStreamWriter>
#include <QPainter>
#include <QColor>
#include "simulation.hpp"
#include <QDebug>

#include "my_query_callback.hpp"
#include "constants.hpp"

Living::Living(int id, Simulation * simulation, Scene *scene, b2World * world, int x, int y, Living * parent, Type type, int DNAsize, float ratio1, float ratio2, float ratio3)
    : QGraphicsItem(),
      simulation(simulation),
      scene(scene),
      body(),
      polygon(),
      radius(simulation->getDemiTile()),
      color(QColor(0,0,0)),
      DNAsize(DNAsize),
      DNA(),
      ratio1(ratio1),
      ratio2(ratio2),
      ratio3(ratio3),
      idCharacter(0),
      id(id),
      type(type),
      energy(0),
      dead(false)
{
    // DNA
    if(!parent)
        setRandomDNA();
    else
    {
        for(int i = 0 ; i < DNAsize ; i++)
        {
            this->DNA.push_back(parent->DNA[i]);
        }
        mutateDNA();
    }
    //  Phenotype
    //  Body
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(x, y);
    body = world->CreateBody(&bodyDef);
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(radius, radius);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    body->CreateFixture(&fixtureDef);
    b2PolygonShape * ppolygonShape = (b2PolygonShape*)body->GetFixtureList()->GetShape();
    for(int i = 0 ; i < ppolygonShape->GetVertexCount() ; i ++)
    {
        polygon.append(QPoint(ppolygonShape->GetVertex(i).x, ppolygonShape->GetVertex(i).y));
    }
    body->SetUserData(this);
    //
    setPos(body->GetPosition().x, body->GetPosition().y);
    setRotation(body->GetAngle());
}

Living::~Living()
{
    body->GetWorld()->DestroyBody(body);
}

QRectF Living::boundingRect() const
{
    return QRectF(-radius,-radius,radius*2,radius*2);
}

void Living::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void)option;
    (void)widget;
    setPos(body->GetPosition().x, body->GetPosition().y);
    setRotation(body->GetAngle());
    painter->setPen(Qt::NoPen);
    painter->setBrush(this->color);
    painter->drawPolygon(polygon);
}


void Living::advance(int step)
{
    if(dead)
        return;
    if (!step)
        return;
}

void Living::buildPhenotype()
{
    qDebug()<< "void Living::buildPhenotype() ";
}

void Living::setRandomDNA()
{
    DNA.clear();
    for(int i = 0 ; i < DNAsize ; i++)
    {
        float gene = rand();
        gene /= (RAND_MAX/2);
        gene -=1;
        DNA.push_back(gene);
    }
}

void Living::setGene(int id, float value)
{
    this->DNA[id] = value;
}

void Living::setCoord(float x, float y)
{
    body->SetTransform(b2Vec2(x, y), body->GetAngle());
}

void Living::mutateDNA()
{
    //  Mutation mineure
    for(int i = 0 ; i < DNAsize ; i++)
    {
        if(rand() < RAND_MAX * ratio1) // ratio apparition mutation
        {
            float rand = std::rand() * 2 - RAND_MAX;
            rand *= ratio2; // ratio importance de la mutation
            rand /=  RAND_MAX;
            DNA[i] += rand;
            if(DNA[i] > 1.0f)
                DNA[i] = 1.0f;
            if(DNA[i] < -1.0f)
                DNA[i] = -1.0f;
        }
    }
    //  Mutation majeure
    if(rand() < RAND_MAX * ratio3)
        setRandomDNA();
}

float Living::getCharacter(unsigned int id, float min, float max)
{
    if(id < DNA.size())
        return DNA[id] * ((max - min)/2) + ((max+min)/2);
    else
    {
        qWarning() << "Dna too small, gene out of range";
    }
    return 0;
}

float Living::getNextCharacter(float min, float max)
{
    idCharacter++;
    return getCharacter(idCharacter-1, min, max);
}

float Living::getX()
{
    return body->GetPosition().x;
}
float Living::getY()
{
    return body->GetPosition().y;
}

void Living::save(QXmlStreamWriter & xml)
{
    xml.writeStartElement("living");
    xml.writeEndElement();
    qDebug() << "void Living::save(QXmlStreamWriter & xml)";
}


float Living::getGene(int geneId)
{
    return DNA[geneId];
}

Living::Type Living::getType()
{
    return this->type;
}

QColor Living::getColor()
{
    return color;
}

float Living::getEnergy()
{
    return energy;
}

void Living::go(int phase)
{
    (void)phase;
    qDebug()  << "void Living::go(int phase)";
}
