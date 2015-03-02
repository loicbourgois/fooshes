#include "foosh.hpp"

#include <QPainter>
#include "simulation.hpp"
#include <QDebug>
#include "constants.hpp"

int Foosh::count = 0;
int Foosh::olderAge = 0;
int Foosh::deaths = 0;
int Foosh::reflexionTime = 0;
float Foosh::globalSpeedMax = 0.0f;
float Foosh::globalAngularSpeedMax = 0.0f;
float Foosh::agingSpeed = 0.0f;
float Foosh::digestionMax = 0.0f;

Foosh * Foosh::olderFoosh = nullptr;

Foosh::Foosh(int id, Simulation * simulation, Scene *scene, b2World * world, int x, int y, Foosh * parent, Type type)
    : Living(id, simulation, scene, world, x, y, parent, type, 1000, 0.1,0.1,0.1),
      eyes(),
      speed(0.0),
      speedMax(0.0f),
      angularSpeed(0.0),
      angularSpeedMax(0.0f),
      age(0),
      speciesAge(0),
      brain()
{
    if(parent)
        speciesAge = parent->getSpeciesAge();
    count++;
    buildPhenotype();
}

Foosh::Foosh(int id, Simulation * simulation, Scene *scene, b2World * world, QXmlStreamReader & xml)
    : Living(id, simulation, scene, world, 0, 0, 0, Living::Type::FOOSH, 0, 0.1f, 0.1f, 0.0f)
{
    count ++;
    load(xml);
    buildPhenotype();
}

Foosh::~Foosh()
{
    count--;
    deaths++;
    //
    for(unsigned int i = 0 ; i < eyes.size() ; i++)
    {
        delete eyes[i];
    }
    eyes.clear();
    delete brain;
    //
    if(count < simulation->getFooshesmin())
        simulation->addLiving(Living::Type::FOOSH);
    if(olderFoosh == this)
    {
        olderAge = 0;
    }
}

void Foosh::save(QXmlStreamWriter &xml)
{
    xml.writeStartElement(ConstantStrings::foosh); // Attributs x 8
    {
        xml.writeTextElement(ConstantStrings::x, QString::number(body->GetPosition().x));
        xml.writeTextElement(ConstantStrings::y, QString::number(body->GetPosition().y));
        xml.writeTextElement(ConstantStrings::angle, QString::number(body->GetAngle()));
        xml.writeTextElement(ConstantStrings::energy, QString::number(energy));
        xml.writeTextElement(ConstantStrings::age, QString::number(age));
        xml.writeTextElement(ConstantStrings::speciesAge, QString::number(speciesAge));
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

void Foosh::load(QXmlStreamReader &xml)
{
    //  8 elements
    float x = 0;
    float y = 0;
    float angle = 0;
    float energy = 0;
    int dnasize = 0;
    QString dnastr;
    int age = 0;
    int species_age = 0;
    //
    while(!xml.atEnd()
          && !(xml.name() == ConstantStrings::foosh && xml.tokenType() == QXmlStreamReader::EndElement))
    {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartElement) // Attributs x 8
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
            if(xml.name() == ConstantStrings::age)
                age = xml.readElementText().toInt();
            if(xml.name() == ConstantStrings::speciesAge)
                species_age = xml.readElementText().toInt();
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
    this->age = age;
    this->speciesAge = species_age;
}





void Foosh::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget)
{
    setPos(body->GetPosition().x, body->GetPosition().y);
    setRotation(body->GetAngle());
    (void)option;
    (void)widget;
    painter->setPen(Qt::NoPen);
    //aura
    if(olderFoosh == this)
    {
        QColor color = QColor(Qt::white);
        color.setAlpha(64);
        painter->setBrush(color);
        painter->drawEllipse(-50, -50, 100, 100);
        //  Eyes - captors
        for(unsigned int i = 0 ; i < eyes.size() ; i++)
        {
            Eye * eye = eyes[i];
            painter->setPen(eye->color);
            painter->drawLine(eye->xmin, eye->ymin, eye->x, eye->y);
        }
    }
    // Body
    painter->setPen(Qt::NoPen);
    painter->setBrush(color);
    painter->drawEllipse(-radius, -radius, radius*2, radius*2);
    // Energy
    float ratioEnergy = energy;
    int r = 255;
    int g = 255;
    if(ratioEnergy>0.5)
        r = (1-ratioEnergy) * 2 * 255;
    if(ratioEnergy<0.5)
        g = ratioEnergy * 2 * 255;
    painter->setBrush(QColor(r, g ,0));
    painter->drawEllipse(-radius/4, -radius, radius/2, radius*2);
    //  Eyes
    painter->setBrush(Qt::white);
    painter->drawEllipse(QPointF(radius/2,radius), radius/2, radius/2);
    painter->drawEllipse(QPointF(-radius/2,radius), radius/2, radius/2);
    painter->setBrush(Qt::black);
    painter->drawEllipse(QPointF(radius/2,radius + radius/4), radius/4, radius/4);
    painter->drawEllipse(QPointF(-radius/2,radius + radius/4), radius/4, radius/4);
}


void Foosh::go(int step)
{
    if(dead)
        return;
    if (!step)
        return;
    else
    {
        //  Age
        age++;
        speciesAge++;
        if(age > olderAge)
        {
            olderAge = age;
            olderFoosh = this;
        }



        //  Eating ?
        b2AABB aabb;
        float x1 = body->GetPosition().x-radius;
        float x2 = body->GetPosition().x+radius;
        float y1 = body->GetPosition().y-radius;
        float y2 = body->GetPosition().y+radius;
        MyQueryCallback query;
        aabb.lowerBound.Set(x1, y1);
        aabb.upperBound.Set(x2, y2);
        body->GetWorld()->QueryAABB( &query, aabb );
        std::vector<b2Body*> foundBodies = query.foundBodies;
        for(unsigned int i = 0 ; i < foundBodies.size() ; i ++)
        {
            b2Body * body = foundBodies[i];
            Living *living = static_cast<Living*>(body->GetUserData());
            if(living != this)
            {
                if(living->getType() == Living::Type::FOOD)
                {
                    if(living)
                    {
                        energy += living->getEnergy() * digestionMax;
                        living->kill();
                    }
                }
            }
        }


        //  Energy
        energy -= agingSpeed;
        if(energy >= 1)
        {
            simulation->addLiving(body->GetPosition().x , body->GetPosition().y, this, Living::Type::FOOSH);
            energy = 0.5f;
        }
        if(energy <= 0)
        {
            dead = true;
            return;
        }
        //  Reflexion
        int r = rand() % Foosh::reflexionTime;
        if(!r)
        {


            //  Eyes
            for(unsigned int i = 0 ; i < eyes.size() ; i++)
            {


                Eye * eye = eyes[i];
                RayCastClosestCallback callback;
                //  TODO
                QPointF a = mapToScene(eye->xmin, eye->ymin);
                QPointF b = mapToScene(eye->xmax, eye->ymax);

                b2Vec2 A(a.x(), a.y());
                b2Vec2 B(b.x(), b.y());

                body->GetWorld()->RayCast(&callback, A, B);

                if (callback.hit)
                {
                    QPointF ey = mapFromScene(callback.point.x, callback.point.y);
                    eye->x = ey.x();
                    eye->y = ey.y();

                    Living *living = (Living *)callback.body->GetUserData();
                    eye->color = living->getColor();
                }
                else
                {
                    eye->x = eye->xmax;
                    eye->y = eye->ymax;
                    eye->color = QColor(0,0,0);
                }
            }


            //  Brain
            std::vector<float> inputs;
            inputs.push_back(1.0f);
            if(speedMax)
                inputs.push_back(speed/speedMax);
            else
                inputs.push_back(0.0f);
            if(angularSpeedMax)
                inputs.push_back(angularSpeed/angularSpeedMax);
            else
                inputs.push_back(0.0f);

            for(unsigned int i = 0 ; i < eyes.size() ; i++)
            {
                Eye * eye = eyes[i];
                float r = eye->getR();
                r /= 255.0f;
                inputs.push_back(r);
                float g = eye->getG();
                g /= 255.0f;
                inputs.push_back(g);
                float b = eye->getB();
                b /= 255.0f;
                inputs.push_back(b);
            }
            brain->compute(inputs);
        }
        //  make choices
        {


            //  move
            speed += brain->getOutput(0);
            if (speed > speedMax )
                speed = speedMax;
            if (speed < -speedMax)
                speed = -speedMax;
            angularSpeed += brain->getOutput(1);
            if (angularSpeed > angularSpeedMax )
                angularSpeed = angularSpeedMax;
            if (angularSpeed < -angularSpeedMax)
                angularSpeed = -angularSpeedMax;


            float andRad = (body->GetAngle() + angularSpeed) * b2_pi / 180.0f ;
            float vX = speed*sin(-andRad);
            float vY = speed*cos(-andRad);
            body->SetTransform(body->GetPosition() + b2Vec2(vX,vY), body->GetAngle()+angularSpeed);
            //
            setPos(body->GetPosition().x, body->GetPosition().y);
            setRotation(body->GetAngle());
        }
        {
            //  Change color
        }
    }
}

void Foosh::buildPhenotype()
{
    energy = 0.5f;
    //
    int eyescount = 10;
    float minangle = 45;
    float maxangle = 135;
    float maxvision = 50;
    float minvision = 5;
    float angleincrement = (maxangle - minangle) / (eyescount-1);
    //  Body
    idCharacter = 0;
    {
        //  colour
        int r = getNextCharacter(0,255);
        int g = getNextCharacter(0,255);
        int b = getNextCharacter(0,255);
        color = QColor(r,g,b);
        //  Max speeds
        speedMax = getNextCharacter(0.0f, globalSpeedMax);
        angularSpeedMax = getNextCharacter(0.0f, globalAngularSpeedMax);
        //  Eyes
        for(float angle = minangle ; angle <= maxangle ; angle += angleincrement)
        {
            eyes.push_back(new Eye(minvision,maxvision,angle));
        }
    }
    //  Brain
    idCharacter = 256;
    {
        int neurons = 10;
        int otherInputs = 3 + 3*eyescount;
        int inputs = neurons + otherInputs;
        int coeffCount = neurons * inputs;
        std::vector<float> coefficients;
        for(int i = 0 ; i < coeffCount ; i++)
        {
            coefficients.push_back(getNextCharacter(-1.0f, 1.0f));
        }
        this->brain = new Brain(neurons, otherInputs, coefficients);
    }
}

void Foosh::reset()
{
    count = 0;
    deaths = 0;
    globalSpeedMax = 0.5f;
    olderAge = 0;
    globalAngularSpeedMax = 1.0f;
    agingSpeed = 0.001f;
    digestionMax = 0.1f;
    reflexionTime = 2;
}

int Foosh::getCount()
{
    return count;
}

int Foosh::getDeaths()
{
    return deaths;
}

int Foosh::getSpeciesAge()
{
    return speciesAge;
}


