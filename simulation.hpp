#pragma once

#include "living.hpp"
#include "constants.hpp"

class MainWindow;
class View;
class Scene;

class Simulation
{
public:
    Simulation(MainWindow * mainWindow, View * view);
    Simulation(MainWindow * mainWindow, View * view, QString path);
    ~Simulation();
    void addLiving(Living::Type type);
    void addLiving(Living::Type type, QXmlStreamReader &xml);
    bool addLiving(int x, int y, Living *living, Living::Type type);
    void deleteOutsiders();
    void advance();
    void update();
    void populate();

    void save(QString path);
    void load(QString path);

    void setWidth(float i);
    void setHeight(float i);
    void setFireGap(float i);
    void setFoodGap(float i);

    void setCpsmax(float i){cpsmax = i;}
    void setFpsmax(float i){fpsmax = i;}
    void setFooshesMin(float i);

    float getWidth() const;
    float getHeight() const;
    float getFireGap() const;
    float getFoodGap() const;

    float getXmin() const;
    float getYmin() const;
    float getXmax() const;
    float getYmax() const;

    float getTile() const;
    float getDemiTile() const;

    float getFpsmax() const{return fpsmax;}
    float getCpsmax() const{return cpsmax;}
    float getFooshesmin() const{return fooshesmin;}
    int getSteps() const{return steps;}
    int getTimeElapsed() const{return elapsedTime;}

private:
    MainWindow * mainWindow;
    View * view;
    Scene * scene;
    b2World * world;

    float width;
    float height;
    float fireGap;
    float foodGap;

    float xmin;
    float ymin;
    float xmax;
    float ymax;

    float tile;
    float demiTile;

    float cpsmax;
    float fpsmax;
    float fooshesmin;

    int steps;
    int elapsedTime;
};
