#include "simulation.hpp"

#include <qdebug.h>
#include <QFile>
#include <QXmlStreamWriter>

#include "main_window.hpp"
#include "view.hpp"
#include "scene.hpp"
#include "living.hpp"
#include "fire.hpp"
#include "food.hpp"
#include "foosh.hpp"

Simulation::Simulation(MainWindow * mainWindow, View * view) :
    mainWindow(mainWindow),
    view(view),
    scene(0),
    world(0),
    width(0),
    height(0),
    fireGap(0),
    foodGap(0),
    tile(10),
    demiTile(5),
    cpsmax(0),
    fpsmax(0),
    fooshesmin(20),
    steps(0),
    elapsedTime(0)
{
    //  Reset
    scene =  new Scene(this);
    view->setScene(scene);
    Foosh::reset();
    Fire::resetCounts();
    Food::reset();
    b2Vec2 gravity(0.0f, 0.0f);
    world = new b2World(gravity);
    //  Settings
    setWidth(3000);
    setHeight(2000);
    setFireGap(90);
    setFoodGap(30);
    setCpsmax(1000);
    setFpsmax(100);
    setFooshesMin(10);
    //  Populate
    populate();
}

void Simulation::populate()
{
    int choice = 0;
    switch(choice)
    {
    case 0: //  Random empty
    {
        addLiving(Living::Type::FIRE);
        addLiving(Living::Type::FOOD);
        addLiving(Living::Type::FOOSH);
        break;
    }
    case 1: //  Random full
    {
        float xmin = getXmin() - ((int)getXmin() % (int)(getFireGap()));
        float ymin = getYmin() - ((int)getYmin() % (int)(getFireGap()));
        for(float x = xmin ; x <= getXmax() ; x += getFireGap())
        {
            for(float y = ymin ; y <=getYmax() ; y += getFireGap())
            {
                addLiving(x, y, 0, Living::Type::FIRE);
            }
        }
        xmin = getXmin() - ((int)getXmin() % (int)(getFoodGap()));
        ymin = getYmin() - ((int)getYmin() % (int)(getFoodGap()));
        for(float x = xmin ; x <= getXmax() ; x += getFoodGap())
        {
            for(float y = ymin ; y <=getYmax() ; y += getFoodGap())
            {
                addLiving(x, y, 0, Living::Type::FOOD);
            }
        }
        for(int i = 0 ; i < fooshesmin ; i++)
            addLiving(Living::Type::FOOSH);
        break;
    }
    case 2: // Green and Blue
    {
        float xmin = getXmin() - ((int)getXmin() % (int)(getFireGap()));
        float ymin = getYmin() - ((int)getYmin() % (int)(getFireGap()));
        for(float x = xmin ; x <= getXmax() ; x += getFireGap())
        {
            for(float y = ymin ; y <=getYmax() ; y += getFireGap())
            {
                addLiving(x, y, 0, Living::Type::FIRE);
            }
        }
        xmin = getXmin() - ((int)getXmin() % (int)(getFoodGap()));
        ymin = getYmin() - ((int)getYmin() % (int)(getFoodGap()));
        for(float x = xmin ; x <= getXmax() ; x += getFoodGap())
        {
            for(float y = ymin ; y <=getYmax() ; y += getFoodGap())
            {
                if(x!=0)
                {
                    addLiving(x, y, 0, Living::Type::FOOD);
                    int r = 0;
                    if(x>0)
                        r = -1;
                    if(x<0)
                        r = 1;
                    int i = scene->items().size()-1;
                    static_cast<Living*>(scene->items()[i])->setGene(0, r);
                    static_cast<Living*>(scene->items()[i])->buildPhenotype();
                }
            }
        }
        for(int i = 0 ; i < fooshesmin ; i++)
            addLiving(Living::Type::FOOSH);
        break;
    }
    default:
    {
        addLiving(Living::Type::FOOD);
        addLiving(Living::Type::FOOSH);
        addLiving(Living::Type::FIRE);
        break;
    }
    }
}



Simulation::Simulation(MainWindow *mainWindow, View *view, QString path):
    mainWindow(mainWindow),
    view(view),
    scene(0),
    world(0),
    width(0),
    height(0),
    fireGap(0),
    foodGap(0),
    tile(10),
    demiTile(5),
    cpsmax(1000),
    fpsmax(100),
    fooshesmin(10),
    steps(0),
    elapsedTime(0)
{
    //  Reset
    scene =  new Scene(this);
    view->setScene(scene);
    Foosh::reset();
    Fire::resetCounts();
    Food::reset();
    b2Vec2 gravity(0.0f, 0.0f);
    world = new b2World(gravity);
    //  load
    load(path);
}

Simulation::~Simulation()
{
    QGraphicsItem * item;
    foreach(item, scene->items())
    {
        static_cast<Living*>(item)->kill();
        scene->removeItem(item);
        delete static_cast<Living*>(item);
    }
    delete world;
    if(scene->items().size())
    {
        qDebug() << "Can not delete the scene ... TODO : find why !?  ";
    }
    else
        delete scene;
}

void Simulation::save(QString path)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();
    xml.writeStartElement("simulation");
    {
        xml.writeTextElement("title", "Simulation");
        xml.writeStartElement("options");
        {
            //  Options x 12
            xml.writeTextElement(ConstantStrings::fpsMax,  QString::number(fpsmax));
            xml.writeTextElement(ConstantStrings::cpsMax,  QString::number(cpsmax));
            xml.writeTextElement(ConstantStrings::width,  QString::number(width));
            xml.writeTextElement(ConstantStrings::height,  QString::number(height));
            xml.writeTextElement(ConstantStrings::fooshesMin,  QString::number(fooshesmin));
            xml.writeTextElement(ConstantStrings::fooshesSpeedMax,  QString::number(Foosh::getSpeedMax()));
            xml.writeTextElement(ConstantStrings::fooshesAngularSpeedMax,  QString::number(Foosh::getAngularSpeedMax()));
            xml.writeTextElement(ConstantStrings::fooshesDigestionMax,  QString::number(Foosh::getDigestionMax()));
            xml.writeTextElement(ConstantStrings::fooshesAgingSpeed,  QString::number(Foosh::getAgingSpeed()));
            xml.writeTextElement(ConstantStrings::foodGap,  QString::number(foodGap));
            xml.writeTextElement(ConstantStrings::foodGrowingSpeed,  QString::number(Food::getGrowingSpeed()));
            xml.writeTextElement(ConstantStrings::fireGap,  QString::number(fireGap));
        }
        xml.writeEndElement();
        xml.writeStartElement("infos");
        {
            //  Infos x 6
            xml.writeTextElement(ConstantStrings::steps,  QString::number(steps));
            xml.writeTextElement(ConstantStrings::elapsedTime,  QString::number(elapsedTime));
            xml.writeTextElement(ConstantStrings::fooshesCount,  QString::number(Foosh::getCount()));
            xml.writeTextElement(ConstantStrings::fooshesDeaths,  QString::number(Foosh::getDeaths()));
            xml.writeTextElement(ConstantStrings::foodCount,  QString::number(Food::getCount()));
            xml.writeTextElement(ConstantStrings::foodEaten,  QString::number(Food::getEatenCount()));
        }
        xml.writeEndElement();
        xml.writeStartElement("livings");
        {
            //  Living x 3
            QGraphicsItem * item;
            Living * living;
            foreach(item, scene->items())
            {
                living = static_cast<Living*>(item);
                living->save(xml);
            }
        }
    }
    xml.writeEndElement();
    xml.writeEndDocument();
    file.close();
}


void Simulation::load(QString path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QXmlStreamReader xml(&file);
    while (!xml.atEnd())
    {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartElement)
        {
            { // Options x 12
                if(xml.name() == ConstantStrings::cpsMax)
                    setCpsmax(xml.readElementText().toFloat());
                if(xml.name() == ConstantStrings::fpsMax)
                    setFpsmax(xml.readElementText().toFloat());
                if(xml.name() == ConstantStrings::width)
                    setWidth(xml.readElementText().toFloat());
                if(xml.name() == ConstantStrings::height)
                    setHeight(xml.readElementText().toFloat());
                if(xml.name() == ConstantStrings::fooshesMin)
                    setFooshesMin(xml.readElementText().toFloat());
                if(xml.name() == ConstantStrings::fooshesSpeedMax)
                    Foosh::setSpeedMax(xml.readElementText().toFloat());
                if(xml.name() == ConstantStrings::fooshesAngularSpeedMax)
                     Foosh::setAngularSpeedMax(xml.readElementText().toFloat());
                if(xml.name() == ConstantStrings::fooshesDigestionMax)
                     Foosh::setDigestionMax(xml.readElementText().toFloat());
                if(xml.name() == ConstantStrings::fooshesAgingSpeed)
                     Foosh::setAgingSpeed(xml.readElementText().toFloat());
                if(xml.name() == ConstantStrings::foodGap)
                    setFoodGap(xml.readElementText().toFloat());
                if(xml.name() == ConstantStrings::foodGrowingSpeed)
                    Food::setGrowingSpeed(xml.readElementText().toFloat());
                if(xml.name() == ConstantStrings::fireGap)
                    setFireGap(xml.readElementText().toFloat());
            }
            {// Infos x 6
                if(xml.name() == ConstantStrings::steps)
                    steps = (xml.readElementText().toInt());
                if(xml.name() == ConstantStrings::elapsedTime)
                    elapsedTime = (xml.readElementText().toInt());
                /*/if(xml.name() == ConstantStrings::fooshesCount)
                    zart(xml.readElementText().toFloat());/*/
                if(xml.name() == ConstantStrings::fooshesDeaths)
                    Foosh::setDeathCount(xml.readElementText().toInt());
                /*/if(xml.name() == ConstantStrings::foodCount)
                    zart(xml.readElementText().toFloat());/*/
                if(xml.name() == ConstantStrings::foodEaten)
                    Food::setEatenCount(xml.readElementText().toInt());

            }
            {// Living x 3
                if(xml.name() == ConstantStrings::food)
                    addLiving(Living::Type::FOOD, xml);
                if(xml.name() == ConstantStrings::fire)
                    addLiving(Living::Type::FIRE, xml);
                if(xml.name() == ConstantStrings::foosh)
                    addLiving(Living::Type::FOOSH, xml);
            }
        }
        if (xml.hasError())
            qDebug() << xml.errorString();
    }
    file.close();
}


void Simulation::addLiving(Living::Type type)
{
    int x = xmin + (rand() % (int)(xmax - xmin + 1));
    int y = ymin + (rand() % (int)(ymax - ymin + 1));
    while(!addLiving(x, y, nullptr, type))
    {
        x = xmin + (rand() % (int)(xmax - xmin + 1));
        y = ymin + (rand() % (int)(ymax - ymin + 1));
    }
}

void Simulation::addLiving(Living::Type type, QXmlStreamReader & xml)
{
    if(type == Living::Type::FOOD)
    {
        scene->addItem(new Food(scene->items().size(), this, scene, world, xml));
    }
    else if(type == Living::Type::FIRE)
    {
        scene->addItem(new Fire(scene->items().size(), this, scene, world, xml));
    }
    else if(type == Living::Type::FOOSH)
    {
        scene->addItem(new Foosh(scene->items().size(), this, scene, world, xml));
    }
}



bool Simulation::addLiving(int x, int y, Living * living, Living::Type type)
{
    switch(type)
    {
    case Living::Type::FIRE :
    {
        int space = fireGap;
        if(x < 0)
            x -=space;
        x += space/2;
        x -= x % space;
        if(y < 0)
            y -=space;
        y += space/2;
        y -= y % space;
        break;
    }
    case Living::Type::FOOD :
    {
        int space = foodGap;
        if(x < 0)
            x -=space;
        x += space/2;
        x -= x % space;
        if(y < 0)
            y -=space;
        y += space/2;
        y -= y % space;
        break;
    }
    case Living::Type::FOOSH :
        break;
    }

    if(x >= xmin
            && x <= xmax
            && y >= ymin
            && y <= ymax)
    {
        switch(type)
        {
        case Living::Type::FIRE :
        {
            scene->addItem(new Fire(scene->items().size(), this, scene, world, x, y, (Fire*)living, type));
            break;
        }
        case Living::Type::FOOD :
        {
            scene->addItem(new Food(scene->items().size(), this, scene, world, x, y, (Food*)living, type));
            break;
        }
        case Living::Type::FOOSH :
        {
            scene->addItem(new Foosh(scene->items().size(), this, scene, world, x, y, (Foosh*)living, type));
            break;
        }
        }
        return true;
    }
    else
    {
        return false;
    }
}

void Simulation::deleteOutsiders()
{
    QGraphicsItem * item;
    Living * living;
    foreach(item, scene->items())
    {
        living = static_cast<Living*>(item);
        if(living->getX() < xmin || living->getX() > xmax
                || living->getY() < ymin || living->getY() > ymax)
        {
            if(living->getType() != Living::Type::FOOSH)
                living->kill();
        }
    }
}

void Simulation::advance()
{
    float32 timeStep = 1.0f / 100.0f;
    int32 velocityIterations = 2;
    int32 positionIterations = 2;
    world->Step(timeStep, velocityIterations, positionIterations);
    scene->advance();
    steps++;
}

void Simulation::update()
{
    scene->update();
}



void Simulation::setWidth(float i)
{
    width = i;
    xmax = width / 2;
    xmin = - xmax;
    view->setSceneRect(xmin*2, ymin*2, width*2, height*2);
}

void Simulation::setHeight(float i)
{
    height = i;
    ymax = height / 2;
    ymin = - ymax;
    view->setSceneRect(xmin*2, ymin*2, width*2, height*2);
}

void Simulation::setFireGap(float i)
{
    float ratio = i / fireGap;

    QGraphicsItem * item;
    Living * living;
    foreach(item, scene->items())
    {
        living = static_cast<Living*>(item);
        if(living->getType() == Living::Type::FIRE)
        {
            living->setCoord(living->getX() * ratio, living->getY() * ratio);
        }
    }
    fireGap = i;
}

void Simulation::setFoodGap(float i)
{
    float ratio = i / foodGap;

    QGraphicsItem * item;
    Living * living;
    foreach(item, scene->items())
    {
        living = static_cast<Living*>(item);
        if(living->getType() == Living::Type::FOOD)
        {
            living->setCoord(living->getX() * ratio, living->getY() * ratio);
        }
    }
    foodGap = i;
}

void Simulation::setFooshesMin(float i)
{
    fooshesmin = i;
    /*for(int i = Foosh::getCount() ; i < fooshesmin ; i++)
    {
        addLiving(Living::Type::FOOSH);
    }*/
}

float Simulation::getWidth() const
{
    return width;
}

float Simulation::getHeight() const
{
    return height;
}

float Simulation::getFireGap() const
{
    return fireGap;
}

float Simulation::getFoodGap() const
{
    return foodGap;
}

float Simulation::getXmin() const
{
    return xmin;
}

float Simulation::getYmin() const
{
    return ymin;
}

float Simulation::getXmax() const
{
    return xmax;
}

float Simulation::getYmax() const
{
    return ymax;
}

float Simulation::getTile() const
{
    return tile;
}

float Simulation::getDemiTile() const
{
    return demiTile;
}


