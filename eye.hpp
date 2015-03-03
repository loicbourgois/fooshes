#pragma once

#include <QColor>

class Eye
{
public:
    Eye(float min, float max, float angle);
    ~Eye();
    int getR();
    int getG();
    int getB();
//private:
    float x;
    float y;
    float xmin;
    float ymin;
    float xmax;
    float ymax;
    QColor color;
};
