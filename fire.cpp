#include "fire.hpp"

#include <simulation.hpp>
#include <Box2D/Box2D.h>
#include <QDebug>
#include "constants.hpp"

#include <QPainter>

int Fire::count = 0;

Fire::Fire(int id, Simulation *simulation, Scene *scene, b2World *world, int x, int y, Fire *parent, Type type)
    : Living(id, simulation, scene, world, x, y, parent, type, 0, 0.0f, 0.0f, 0.0f)
{
    count++;
    buildPhenotype();
}

Fire::Fire(int id, Simulation *simulation, Scene *scene, b2World *world, QXmlStreamReader &xml) :
    Living(id, simulation, scene, world, 0, 0, 0, Living::Type::FIRE, 0, 0, 0, 0)
{
    count ++;
    load(xml);
    buildPhenotype();
}

void Fire::save(QXmlStreamWriter &xml)
{
    xml.writeStartElement(ConstantStrings::fire); // Attributs x 4
    {
        xml.writeTextElement(ConstantStrings::x, QString::number(body->GetPosition().x));
        xml.writeTextElement(ConstantStrings::y, QString::number(body->GetPosition().y));
        xml.writeTextElement(ConstantStrings::angle, QString::number(body->GetAngle()));
        xml.writeTextElement(ConstantStrings::energy, QString::number(energy));
    }
    xml.writeEndElement();
}

void Fire::load(QXmlStreamReader & xml)
{
    float x = 0;
    float y = 0;
    float angle = 0;
    float energy = 0;
    //
    while(!xml.atEnd()
          && !(xml.name() == ConstantStrings::fire && xml.tokenType() == QXmlStreamReader::EndElement))
    {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartElement) // Attributs x 4
        {
            if(xml.name() == ConstantStrings::x)
                x = xml.readElementText().toFloat();
            if(xml.name() == ConstantStrings::y)
                y = xml.readElementText().toFloat();
            if(xml.name() == ConstantStrings::angle)
                angle = xml.readElementText().toFloat();
            if(xml.name() == ConstantStrings::energy)
                energy = xml.readElementText().toFloat();

        }
    }
    //
    this->energy = energy;
    body->SetTransform(b2Vec2(x, y), angle);
}





void Fire::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void)option;
    (void)widget;
    setPos(body->GetPosition().x, body->GetPosition().y);
    setRotation(body->GetAngle());
    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawPolygon(polygon);
}

void Fire::buildPhenotype()
{
    energy = 1.0f;
    color = QColor(255,0,0);
}

void Fire::resetCounts()
{
    count = 0;
}

Fire::~Fire()
{
    count--;
    if(count < 1)
        simulation->addLiving(type);
}

void Fire::go(int step)
{
    if(dead)
        return;
    if (!step)
        return;
    //  Reproduction
    int r = rand() % 1000;
    if(!r)
    {
        int space = simulation->getFireGap();
        // Where to look ?
        int r = rand() % 4;
        switch(r)
        {
        /*case 0:
            simulation->addLiving(body->GetPosition().x, body->GetPosition().y + space, this, Living::Type::FIRE);
            break;
        case 1:
            simulation->addLiving(body->GetPosition().x + space, body->GetPosition().y, this, Living::Type::FIRE);
            break;
        case 2:
            simulation->addLiving(body->GetPosition().x, body->GetPosition().y - space, this, Living::Type::FIRE);
            break;
        case 3:
            simulation->addLiving(body->GetPosition().x - space, body->GetPosition().y, this, Living::Type::FIRE);
            break;*/
        case 0:
            simulation->addLiving(body->GetPosition().x + space, body->GetPosition().y + space, this, Living::Type::FIRE);
            break;
        case 1:
            simulation->addLiving(body->GetPosition().x + space, body->GetPosition().y - space, this, Living::Type::FIRE);
            break;
        case 2:
            simulation->addLiving(body->GetPosition().x - space, body->GetPosition().y + space, this, Living::Type::FIRE);
            break;
        case 3:
            simulation->addLiving(body->GetPosition().x - space, body->GetPosition().y - space, this, Living::Type::FIRE);
            break;

        }
    }
    //  Killing
    r = rand() % 2;
    if(r)
    {
        b2AABB aabb;
        float x1 = body->GetPosition().x-simulation->getDemiTile();
        float x2 = body->GetPosition().x+simulation->getDemiTile();
        float y1 = body->GetPosition().y-simulation->getDemiTile();
        float y2 = body->GetPosition().y+simulation->getDemiTile();
        MyQueryCallback query;
        aabb.lowerBound.Set(x1, y1);
        aabb.upperBound.Set(x2, y2);
        body->GetWorld()->QueryAABB( &query, aabb );
        std::vector<b2Body*> foundBodies = query.foundBodies;
        for(unsigned int i = 0 ; i < foundBodies.size() ; i ++)
        {
            b2Body * aa = foundBodies[i];
            Living * uu = static_cast<Living*>(aa->GetUserData());
            if(uu != this)
                uu->kill();
        }
    }
    //  Energy
    /*energy -= 0.001;
    if(energy < 0.0f)
        kill();*/
    //  Position
}
