#include "food.hpp"

#include "scene.hpp"
#include <Box2D/Box2D.h>
#include <QPainter>
#include <QColor>
#include "simulation.hpp"
#include "constants.hpp"
#include <QDebug>

int Food::count = 0;
int Food::eatenCount = 0;
float Food::growingSpeed = 0;

Food::Food(int id, Simulation * simulation, Scene *scene, b2World * world, int x, int y, Food * parent, Type type)
    : Living(id, simulation, scene, world, x, y, parent, type, 1, 0.1f, 0.1f, 0.0f)
{
    count ++;
    buildPhenotype();
}

Food::Food(int id, Simulation * simulation, Scene *scene, b2World * world, QXmlStreamReader & xml)
    : Living(id, simulation, scene, world, 0, 0, 0, Living::Type::FOOD, 0, 0.1f, 0.1f, 0.0f)
{
    count ++;
    load(xml);
    buildPhenotype();
}

Food::~Food()
{
    count--;
    eatenCount++;
    if(count < 1)
        simulation->addLiving(Living::Type::FOOD);
}

void Food::save(QXmlStreamWriter &xml)
{
    xml.writeStartElement(ConstantStrings::food); // Attributs x 6
    {
        xml.writeTextElement(ConstantStrings::x, QString::number(body->GetPosition().x));
        xml.writeTextElement(ConstantStrings::y, QString::number(body->GetPosition().y));
        xml.writeTextElement(ConstantStrings::angle, QString::number(body->GetAngle()));
        xml.writeTextElement(ConstantStrings::energy, QString::number(energy));
        xml.writeTextElement(ConstantStrings::dnaSize, QString::number(DNA.size()));
        QString dnastr;
        for(unsigned int i = 0 ; i < DNA.size() ; i++)
        {
            dnastr += QString::number(DNA[i]) + ";";
        }
        dnastr.remove(dnastr.size()-1, 1);
        xml.writeTextElement(ConstantStrings::dna, dnastr);
    }
    xml.writeEndElement();
}

void Food::load(QXmlStreamReader &xml)
{
    float x = 0;
    float y = 0;
    float angle = 0;
    int dnasize = 0;
    QString dnastr;
    float energy = 0;
    //
    while(!xml.atEnd()
          && !(xml.name() == ConstantStrings::food && xml.tokenType() == QXmlStreamReader::EndElement))
    {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartElement) // Attributs x 6
        {
            if(xml.name() == ConstantStrings::x)
                x = xml.readElementText().toFloat();
            if(xml.name() == ConstantStrings::y)
                y = xml.readElementText().toFloat();
            if(xml.name() == ConstantStrings::angle)
                angle = xml.readElementText().toFloat();
            if(xml.name() == ConstantStrings::energy)
                energy = xml.readElementText().toFloat();
            if(xml.name() == ConstantStrings::dnaSize)
                dnasize = xml.readElementText().toFloat();
            if(xml.name() == ConstantStrings::dna)
                dnastr = xml.readElementText();
        }
    }
    //
    this->energy = energy;
    body->SetTransform(b2Vec2(x, y), angle);
    this->DNAsize = dnasize;
    QStringList list = dnastr.split(';');
    if(list.size() == this->DNAsize)
    {
        DNA.clear();
        for (int i = 0; i < list.size(); ++i)
        {
            DNA.push_back(list[i].toFloat());
        }
    }
    else
    {
        qWarning() << "DNA size doesn't match";
    }
}

void Food::buildPhenotype()
{
    idCharacter = 0;
    r = 0.0f;
    float ratio = getNextCharacter(-1.0f, 1.0f);
    if(ratio == 0.0f)
    {
        g = 255.0f;
        b = 255.0f;
    }
    else if(ratio > 0)
    {
        g = 255.0f;
        b = 255.0f * (1.0f - ratio);
    }
    else if(ratio < 0)
    {
        g = 255.0f * (1.0f + ratio);
        b = 255.0f;
    }
}

void Food::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                 QWidget *widget)
{
    (void) option;
    (void) widget;
    setPos(body->GetPosition().x, body->GetPosition().y);
    setRotation(body->GetAngle());
    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawPolygon(polygon);
}

void Food::go(int step)
{
    if(dead)
        return;
    if (!step)
        return;
    else
    {
        //  Energy
        energy += growingSpeed;
        if(energy > 1.0f)
        {
            energy = 1;
            //
            int r = rand() % 100;
            if(!r)
            {
                int space = simulation->getFoodGap();
                MyQueryCallback queryCallback;
                b2AABB aabb;
                float x1 = body->GetPosition().x-simulation->getDemiTile()*0.9f;
                float x2 = body->GetPosition().x+simulation->getDemiTile()*0.9f;
                float y1 = body->GetPosition().y-simulation->getDemiTile()*0.9f;
                float y2 = body->GetPosition().y+simulation->getDemiTile()*0.9f;
                // Where to look ?
                int r = rand() % 4;
                switch(r)
                {
                case 0:
                    aabb.lowerBound.Set(x1, y1+space);
                    aabb.upperBound.Set(x2, y2+space);
                    body->GetWorld()->QueryAABB( &queryCallback, aabb );
                    if(!queryCallback.foundBodies.size()){
                        if(simulation->addLiving(body->GetPosition().x, body->GetPosition().y + space, this, Living::Type::FOOD))
                            energy = 0.5f;
                    }
                    break;
                case 1:
                    aabb.lowerBound.Set(x1+space, y1);
                    aabb.upperBound.Set(x2+space, y2);
                    body->GetWorld()->QueryAABB( &queryCallback, aabb );
                    if(!queryCallback.foundBodies.size()){
                        if(simulation->addLiving(body->GetPosition().x + space , body->GetPosition().y, this, Living::Type::FOOD))
                            energy = 0.5f;
                    }
                    break;
                case 2:
                    aabb.lowerBound.Set(x1, y1-space);
                    aabb.upperBound.Set(x2, y2-space);
                    body->GetWorld()->QueryAABB( &queryCallback, aabb );
                    if(!queryCallback.foundBodies.size()){
                        if(simulation->addLiving(body->GetPosition().x, body->GetPosition().y - space, this, Living::Type::FOOD))
                            energy = 0.5f;
                    }
                    break;
                case 3:
                    aabb.lowerBound.Set(x1-space, y1);
                    aabb.upperBound.Set(x2-space, y2);
                    body->GetWorld()->QueryAABB( &queryCallback, aabb );
                    if(!queryCallback.foundBodies.size()){
                        if(simulation->addLiving(body->GetPosition().x - space , body->GetPosition().y, this, Living::Type::FOOD))
                            energy = 0.5f;
                    }
                    break;
                }
            }
        }
        //  Couleur
        color = QColor(r * energy, g * energy, b * energy);
        //  Position


    }
}

int Food::getCount()
{
    return count;
}

int Food::getEatenCount()
{
    return eatenCount;
}

void Food::reset()
{
    count = 0;
    eatenCount = 0;
    growingSpeed = 0.001f;
}
