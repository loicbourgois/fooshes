#include "eye.hpp"

#include <Box2D/Box2D.h>

Eye::Eye(float min, float max, float angle)
{
    float angleRAD = angle * b2_pi / 180.0f;
    xmin = min * cosf(angleRAD);
    ymin = min * sinf(angleRAD);
    xmax = max * cosf(angleRAD);
    ymax = max * sinf(angleRAD);
}

Eye::~Eye()
{

}

int Eye::getR()
{
    return color.red();
}

int Eye::getG()
{
    return color.green();
}

int Eye::getB()
{
    return color.blue();
}

